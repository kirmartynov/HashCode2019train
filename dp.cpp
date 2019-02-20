#include "util.cpp"
#include <unordered_map>

using namespace std;

using Row = vector<int>;
using Grid = vector<Row>;
using Shadow = pair<Row, Row>;

namespace std
{
	template<> struct hash<Row>
	{
		typedef Row argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& row) const noexcept
		{
			result_type h = 0;
			for (auto& value : row)
				h = std::hash<int>{}(value) ^ (h * 3);
			return h;
		}
	};
	template<> struct hash<Shadow>
	{
		typedef Shadow argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& shadow) const noexcept
		{
			result_type const h1 ( std::hash<Row>{}(shadow.first) );
			result_type const h2 ( std::hash<Row>{}(shadow.second) );
			return h1 ^ (h2 * 257); // or use boost::hash_combine (see Discussion)
		}
	};
};

namespace stuff
{
	template<typename ContainerT, typename PredicateT>
	void erase_if(ContainerT& items, const PredicateT& predicate)
	{
		for (auto it=items.begin() ; it != items.end() ; )
			if (predicate(*it))
				it = items.erase(it);
			else
				++it;
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int r, c, l, h;
	cin >> r >> c >> l >> h;

	Grid grid(r, Row(c));
	for (auto& row : grid)
	{
		string line;
		cin >> line;

		for (int x=0 ; x<c ; ++x)
			row[x] = line[x] == 'T';
	}

	Grid sums(r+1, Row(c+1));
	for (int y=0 ; y<r ; ++y)
	for (int x=0 ; x<c ; ++x)
		sums[y+1][x+1] = grid[y][x] + sums[y+1][x] + sums[y][x+1] - sums[y][x];

	vector<vector<vector<pair<int, int>>>> rects(r, vector<vector<pair<int, int>>>(c));
	for (int y=0 ; y<r ; ++y)
	for (int x=0 ; x<c ; ++x)
	{
		for (int dy=1 ; dy<=h ; ++dy)
		for (int dx=1 ; dx*dy<=h ; ++dx)
		{
			if (y+dy > r)
				continue;
			if (x+dx > c)
				continue;
			int area = dx*dy;
			int ts = sums[y+dy][x+dx] - sums[y+dy][x] - sums[y][x+dx] + sums[y][x];
			int ms = area - ts;

			if (ts >= l && ms >= l)
				rects[y][x].push_back({ dy, dx });
		}
	}

	auto check = [&](const Shadow& shadow, int y, int x, pair<int, int> rect)
	{
		for (int dy=0 ; dy<rect.first ; ++dy)
			if (shadow.first[y+dy] > x)
				return false;
		for (int dx=0 ; dx<rect.second ; ++dx)
			if (shadow.second[x+dx] > y)
				return false;
		return true;
	};
	auto extend = [&](Shadow shadow, int y, int x, pair<int, int> rect)
	{
		for (int dy=0 ; dy<rect.first ; ++dy)
			shadow.first[y+dy] = max(shadow.first[y+dy], x+rect.second);
		for (int dx=0 ; dx<rect.second ; ++dx)
			shadow.second[x+dx] = max(shadow.second[x+dx], y+rect.first);
		return shadow;
	};

	unordered_map<Shadow, int> dp;
	dp[Shadow(Row(r), Row(c))] = 0;
	for (int y=0 ; y<r ; ++y)
	for (int x=0 ; x<c ; ++x)
	{
		using stuff::erase_if;
		erase_if(dp, [&](pair<const Shadow, int>& entry)
		{
			for (auto& sy : entry.first.first)
				if (sy >= y)
					return false;
			for (auto& sx : entry.first.second)
				if (sx >= x)
					return false;
			return true;
		});
		for (auto dyx : rects[y][x])
		{
			int area = dyx.first * dyx.second;
			vector<pair<Shadow, int>> add;
			for (auto& entry : dp)
			{
				if (!check(entry.first, y, x, dyx))
					continue;
				add.emplace_back(extend(entry.first, y, x, dyx), entry.second+area);
			}
			for (auto& entry : add)
			{
				auto& score = dp[move(entry.first)];
				score = max(score, entry.second);
			}
		}
	}

	int score = 0;
	for (auto& entry : dp)
		score = max(score, entry.second);

	cerr << "Score: " << score << "\n";
}
