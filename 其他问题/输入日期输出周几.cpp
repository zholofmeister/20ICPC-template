输入年月日，例如2010-08-15,就调用calc(2010,8,15)
输出0代表周日,1代表周一....,6代表周日

int calc(int y,int m,int d)
{
    if(m==1 || m==2)
        {
        m+=12;
        --y;
    }
    int w=(d+1+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
    return w;
}