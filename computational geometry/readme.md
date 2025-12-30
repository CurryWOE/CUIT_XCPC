#! https://zhuanlan.zhihu.com/p/563140295
# 计算几何导读
# 正弦定理
$\frac{a}{\sin A}=\frac{b}{\sin B}=\frac{c}{sin C}=2r$

r为外接圆半径
# 余弦定理
$\cos A=\frac{b^2+c^2-a^2}{2bc}$

$\cos B=\frac{a^2+c^2-b^2}{2ac}$

$\cos C=\frac{a^2+b^2-c^2}{2ab}$
# 浮点数最大公约数
fmod,<cmath>,计算除法操作 x / y 的浮点余数,返回值的符号与 x 相同

EPS应该略小于根据题目数据范围所能得到的最小gcd
```cpp
double fgcd(double x,double y)
{
    if(fabs(x)<EPS)
        return y;
    if(fabs(y)<EPS)
        return x;
    return fgcd(y,fmod(x,y));
}
```
# 点积
向量点积，几何意义是$|a||b|cos(a,b)$，结果表示夹角情况，正锐角，0直角，负钝角
# 叉积
向量叉积，几何意义是$|a||b|sin(a,b)$，结果表示向量共起点时，只考虑180以内的夹角，b在a的什么方向，正逆时针，0共线，负顺时针
# 极坐标系
在平面上取一定点 $O$，从 $O$ 引一条水平射线 $Ox$，规定方向自左至右，再选定一个长度单位并规定角旋转的正方向为逆时针方向，这样就构成了一个极坐标系

点O叫作极点（类似笛卡尔坐标系的原点）

射线叫作极轴（类似笛卡尔坐标系的x正半轴）

极坐标系中的点 $A$ 用 $(r,\theta)$ 表示，极径$r=|OA|$，极角$\theta=\angle AOx$

设两点的极坐标为 $(r_1, \theta_1)和(r_2, \theta_2)$,那么两点的欧式距离为

$\left \| \mathbf{p} - \mathbf{q} \right \| = \sqrt{r_1^2 - 2r_1r_2 \cos (\theta_1 - \theta_2) + r_2^2}$
# 极角序
选定极点，其他点按照极角排序，如果在坐标系的上下两边，上边大于下边，如果同边按叉积升序
# 距离
设点 $A(x_1,y_1),B(x_2,y_2)$
# 曼哈顿距离
$dis=|x_1-x_2|+|y_1-y_2|$

u和v的k维曼哈顿距离可以用 $a$ 序列表示，其中 $a_i\in\{0,1\}$，因此 $a$ 总共有 $2^k$ 个。而曼哈顿距离一定是其中最大值，因为曼哈顿距离是绝对值相加

$$dis_{u,v}=\max\limits_{\forall a}\{\sum\limits_{i=1}^k(-1)^{a_i}(u_i-v_i)\}$$

设 $f(a,u)=\sum\limits_{i=1}^k(-1)^{a_i}u_i$，则距离为 $\max\{f(a,u)-f(a,v)\}$

记 $\overline a$ 表示 $a$ 的每位取反，则距离为 $\max\{f(a,u)+f(\overline a,v)\}$

因此空间中最远两点距离是，预处理 $g(a)=\max\limits_{\forall u}\{f(a,u)\}$

$ans=\max\limits_{\forall a}\{g(a)+g(\overline a)\}$
# 切比雪夫距离
$dis=max(|x_1-x_2|,|y_1-y_2|)$
# 曼哈顿距离与切比雪夫距离的相互转化
点 $(x,y)$ 转化为 $(x+y,x-y)$，新坐标系的切比雪夫距离就是原坐标系的曼哈顿距离

点 $(x,y)$ 转化为 $(\frac{x+y}2,\frac{x-y}2)$，新坐标系的曼哈顿距离就是原坐标系的切比雪夫距离

# 零散结论
多边形外角和360

凸包周长，涉及圆弧的，只在圆弧处转弯的，圆弧拼起来一点是360，感性理解是从起点再回到起点，由于只在圆弧转弯，一定是360