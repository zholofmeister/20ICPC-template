1. 给你一个多边形，看给出的点是按顺时针还是按逆时针给的
对于凸多边形，看一个点和旁边的点的叉积就行了
对于n个点的普通多边形，要做n次i点和i+1点（n点是0点）的叉积，然后加起来，如果是负数就为逆时针，如果是正数就为顺时针