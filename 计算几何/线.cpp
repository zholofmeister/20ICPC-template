struct Line {
    Point s, e;
    Line() {}
    Line(Point _s, Point _e) {
        s = _s;
        e = _e;
    }
    bool operator == (Line v) {return (s == v.s) && (e == v.e);}
    //根据一个点和倾斜角 angle 确定直线，0 <= angle < pi
    Line (Point p, double angle) {
        s = p;
        if (sgn(angle - pi / 2) == 0) {
            e = (s + Point(0, 1));
        } else {
            e = (s + Point(1, tan(angle)));
        }
    }
    //ax + by + c == 0
    Line(double a, double b, double c) {
        if (sgn(a) == 0) {
            s = Point(0, -c / b);
            e = Point(1, -c / b);
        } else if (sgn(b) == 0) {
            s = Point(-c / a, 0);
            e = Point(-c / a, 1);
        } else {
            s = Point(0, -c / b);
            e = Point(1, (-c - a) / b);
        }
    }
    void input() { s.input();e.input();}
    void adjust() {if (e < s) swap(s, e);}
    //求线段长度
    double length() {return s.distance(e);}
    //返回直线倾斜角
    double angle() {
        double k = atan2(e.y - s.y, e.x - s.x);
        if (sgn(k) < 0) k += pi;
        if (sgn(k - pi) == 0) k -= pi;
        return k;
    //点和直线关系  要保证s.y>e.y，如<要swap
    }
    //1 线在点的左侧
    //2 线在点的右侧
    //3 点在直线上
    int relation(Point p) {
        int c = sgn((p - s) ^ (e - s));
        if (c < 0) return 1;
        else if (c > 0) return 2;
        else return 3;
    }
    //点在线段上的判断
    bool pointonseg(Point p) {return sgn((p - s) ^ (e-s)) == 0 && sgn((p - s) * (p - e)) <= 0;}
    //两向量平行（对应直线平行或重合）
    bool parallel(Line v) {return sgn((e - s) ^ (v.e - v.s)) == 0;}
    //两线段相交判断
    //2 规范相交
    //1 非规范相交
    //0 不相交
    int segcrossseg(Line v) {
        int d1 = sgn((e - s) ^ (v.s - s));
        int d2 = sgn((e - s) ^ (v.e - s));
        int d3 = sgn((v.e - v.s) ^ (s - v.s));
        int d4 = sgn((v.e - v.s) ^ (e - v.s));
        if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) return 2;
        return (d1 == 0 && sgn((v.s - s) * (v.s - e)) <= 0) ||
            (d2 == 0 && sgn((v.e - s) * (v.e - e)) <= 0) ||
            (d3 == 0 && sgn((s - v.s) * (s - v.e)) <= 0) ||
            (d4 == 0 && sgn((e - v.s) * (e - v.e)) <= 0);
    }
    //直线和线段相交判断
    //-*this line -v seg
    //2 规范相交
    //1 非规范相交
    //0 不相交
    int linecrossseg(Line v) {
        int d1 = sgn((e - s) ^ (v.s - s));
        int d2 = sgn((e - s) ^ (v.e - s));
        if ((d1 ^ d2) == -2) return 2;
        return (d1 == 0 || d2 == 0);
    }
    //两直线关系
    //0 平行
    //1 重合
    //2 相交
    int linecrossline(Line v) {
        if ((*this).parallel(v))
            return v.relation(s) == 3;
        return 2;
    }
    //求两直线的交点
    //要保证两直线不平行或重合
    Point crosspoint(Line v) {
        double a1 = (v.e - v.s) ^ (s - v.s);
        double a2 = (v.e - v.s) ^ (e - v.s);
        return Point((s.x * a2 - e.x * a1) / (a2 - a1),
                     (s.y * a2 - e.y * a1) / (a2 - a1));
    }
    //点到直线的距离 
	//测试 : cf614C
    double dispointtoline(Point p) {return fabs((p - s) ^ (e - s)) / length();}
    //点到线段的距离
	//测试 : cf614C
    double dispointtoseg(Point p) {
        if (sgn((p - s) * (e - s)) < 0 || sgn((p - e) * (s - e)) < 0)
            return min(p.distance(s), p.distance(e));
        return dispointtoline(p);
    }
    //返回线段到线段的距离
    //前提是两线段不相交，相交距离就是0了
    double dissegtoseg(Line v) {
        return min(min(dispointtoseg(v.s), dispointtoseg(v.e)),
                   min(v.dispointtoseg(s), dispointtoseg(e)));
    }
    //返回p在直线上的投影
    Point lineprog(Point p) {return s + ( ((e - s) * ((e - s) * (p - s))) / ((e - s).len2()) );}
    //返回点p关于直线的对称点
    Point symmetrypoint(Point p) {
        Point q = lineprog(p);
        return Point(2 * q.x - p.x, 2 * q.y - p.y);
    }
};