POJ 1228 数据水
所谓稳定凸包就是不存在凸包外加入一个点使得形成的新凸包还包括原凸包的所有点。
所以求完凸包后的每条边上至少要有三个点
题意：
有一个多边形的凸包，但这个凸包上一条边有可能除了两条端点还有点，现在拿掉不知道多少个点，问剩下的点是不是稳定凸包？
既判断这n个点连成的多边形是不是稳定凸包？
思路：
1. 如果点数<6，那么肯定不是稳定凸包。
2. 如果所有点都共线，那么肯定不是稳定凸包。
3. 对剩下的这n个点求凸包，然后枚举凸包的每条边，看原多边形是否有一个不是这条边的两个端点的点在这条线上。如果每条边都有，那就是稳定凸包了。