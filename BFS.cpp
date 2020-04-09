
//地上有一个m行n列的方格，从坐标[0, 0] 到坐标[m - 1, n - 1] 。一个机器人从坐标[0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格[35, 37] ，因为3 + 5 + 3 + 7 = 18。但它不能进入方格[35, 38]，因为3 + 5 + 3 + 8 = 19。请问该机器人能够到达多少个格子？
//
//
//
//来源：力扣（LeetCode）
//链接：https ://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

#include <iostream>
#include<string>
#include<vector>
#include <queue>
using namespace std;
int countNum(int x)
{
	int res = 0;
	for (x; x != 0; x /= 10)
	{
		res = res + x % 10;
	}
	return res;
}
int main()
{
	int m, n, k;
	cin >> m >> n >> k;
	if (!k)
		return 1;
	queue<pair<int, int>> pos;
	int dx[2]{ 0,1 };//右下移动
	int dy[2]{ 1,0 };
	vector<vector<int>> vis(m, vector<int>(n, 0));//是否遍历
	pos.push(make_pair(0, 0));
	vis[0][0] = 1;
	int ans = 1;
	while (!pos.empty())
	{
		int x = pos.front().first;
		int y = pos.front().second;
		pos.pop();
		for (int i = 0; i < 2; i++)
		{
			int tx = x + dx[i];
			int ty = y + dy[i];
			if (tx < 0 || tx >= m || ty<0 || ty >= n || vis[tx][ty] || countNum(tx) + countNum(ty)>k)
				continue;
			pos.push(make_pair(tx,ty));
			vis[tx][ty] = 1;
			ans++;
		}
	}
	return ans;


}

