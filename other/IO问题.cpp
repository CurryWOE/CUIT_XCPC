/*
读取一行，一行有未知个数
*/
pair<int,int> solve(string s)
{
    int c = s[0] == '+'?1:-1;
    int res = 0, len = s.size();
    for (int i = 1; i < len; i++)
        res = res * 10 + s[i] - '0';
    return {res, c};
}
string s;
getline(cin, s);
stringstream ss;
ss << s;
while(ss >> s)
{
    auto res = solve(s);

}