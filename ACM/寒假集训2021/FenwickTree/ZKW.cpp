/*  @author:        voidf 
    @tested_date:   2021.1.27
    ZKW线段树两个板子：差分版和带tag版

    (过)(度)(封)(装)
     面  向  对  象 设计，需要C++11

    带tag版可以解决区间相加、相乘、求模求和和RMQ问题
    差分版只能解决区间加法和RMQ问题

    实际使用上如果只是RMQ问题，差分版快一些（废话

    *本板子中虽然没有用private限制，但所有带inline的方法都是不推荐外部调用的

    带tag版线段树api:
        创建一个线段树:
            ZKW::ZKW_Tag<类型> 线段树的名字(源序列, 长度, 是否在源序列上构建线段树)
        用例1：
            long long *arr = new long long[n << 5];
            ZKW::ZKW_Tag<long long> tree(arr, n, true);
        用例2：
            ZKW::ZKW_Tag<long long> tree(arr, n, false);

            # 线段树构造函数最后一个参数为true时，会用cin直接读入长度为n的数据装进树节点里
            # 此时不要往源序列里面读入数据，源序列只是一块分配给线段树用的空间而已
            # 此时请确保你源序列数组开得够大，足够放下整棵树。树最大可能根据你的选项占用掉(5*T+int)*n*4的空间
            # 其中T是你指定的类型，可以是long long, int, double, float这些基本类型，如果要传入类请根据底下说明重载一些运算符
            
            # 如果为false，则线段树会自动用new申请一块足够的空间，并用源序列中的数据建树
            # 初始化时所传源序列下标从0开始，但实例化的树中下标都是以1开始
            # 注意这样不能空间复用，多组样例情况下慎用
        区间加法：
            tree.range_add(l, r, value)
            # 向树中闭区间[l,r]中所有元素加上value值，下标从1开始
        区间乘法：
            tree.range_mul(l, r, value)
            # 向树中闭区间[l,r]中所有元素乘上value值，下标从1开始
        区间求和：
            tree.query_sum(l, r)
            # 求树中闭区间[l,r]中所有元素的和，下标从1开始
        全局求模：
            修改变量MO的值即可
        区间最大值：
            tree.query_max(l, r)
            # 求树中闭区间[l,r]中所有元素的最大值，下标从1开始
        区间最小值：
            tree.query_min(l, r)
            # 求树中闭区间[l,r]中所有元素的最小值，下标从1开始
        打印线段树：
            tree.show()
        遍历线段树：
            for(auto i:tree)

    差分版线段树api:
        创建一个线段树:
            ZKW::ZKW_Dif<类型> 线段树的名字(源序列, 长度, 是否在源序列上构建线段树)
        区间最大值：
            tree.query_max(l, r)
            # 求树中闭区间[l,r]中所有元素的最大值，下标从1开始
        区间最小值：
            tree.query_min(l, r)
            # 求树中闭区间[l,r]中所有元素的最小值，下标从1开始
        区间加法：
            tree.range_add(l, r, value)
            # 向树中闭区间[l,r]中所有元素加上value值，下标从1开始
        获取某下标处的值：
            tree.getval(ind)
            # 获取ind下标处的值，下标从1开始
        打印线段树：
            tree.show()
        遍历线段树：
            for(auto i:tree)

    编译开关：见88行
        REQUIRE_TAG             define后，会在节点中增加sum_content, length, lazy_add三个字段，tag型线段树必选
        REQUIRE_RMQ             define后才能解决RMQ问题，增加max_content, min_content字段，差分型必选
        REQUIRE_MULTIPLY_TAG    define后才能解决区间乘法，增加lazy_mul字段
        MODULO                  define后启用全局求模，模数为define指定的变量
*/
#include <iostream>
#include <stack>
#include <cstring>
#include <new>
// #pragma GCC diagnostic warning "-std=c++11"
using std::max;
using std::min;

#define REQUIRE_TAG // 使用带tag的zkw线段树（默认得用这个），每个节点占用的空间会增加一个int和一个尖括号指定的类型
// #define REQUIRE_RMQ          // 解决RMQ问题的开关，使用差分型线段树，或者用带tag线段树解决RMQ问题时使用
#define REQUIRE_MULTIPLY_TAG // 乘法标记开关
#define MODULO MO
int MO;
namespace ZKW // zkw线段树
{
    template <typename T>
    struct ZKW_Node
    {
#ifdef REQUIRE_TAG
        int length;
        T lazy_add;
        T sum_content;
#ifdef REQUIRE_MULTIPLY_TAG
        T lazy_mul;
#endif
#endif
#ifdef REQUIRE_RMQ
        T max_content;
        T min_content;
#endif
    };
    template <typename T> // 使用的类T必须支持= （问就是你常用的int, long long, double甚至__int128都是支持的）
    struct ZKW_Base
    {
        using _Node = ZKW_Node<T>;
        // typedef ZKW_Node<T> _Node;
        int len;        // 线段树实际节点数
        int valid_len;  // 原有效数据长度
        _Node *_start;  // 起始位置
        _Node *_finish; // 结束位置
        int M;          // 最高位的下一位

        ZKW_Base(T arr[], int length, bool direct_build = false) // 这里的direct_build是直接读进线段树里
        {
            M = 1 << (32 - __builtin_clz(length + 1));
            valid_len = length;
            len = M << 1;
            if (direct_build)
            {
                _start = ::new (arr) _Node[len]; // 会占用arr序列的空间
                for (int idx = 0; idx < length; idx++)
                {
#ifdef REQUIRE_TAG
                    std::cin >> _start[idx + M + 1].sum_content;
                    _start[idx + M + 1].length = 1;
                    _start[idx + M + 1].lazy_add = 0;

#ifdef REQUIRE_MULTIPLY_TAG
                    _start[idx + M + 1].lazy_mul = 1;
#endif
#ifdef REQUIRE_RMQ
                    _start[idx + M + 1].min_content = _start[idx + M + 1].max_content = _start[idx + M + 1].sum_content;
#endif
#elif defined(REQUIRE_RMQ)
                    std::cin >> _start[idx + M + 1].max_content;
                    _start[idx + M + 1].min_content = _start[idx + M + 1].max_content;
#endif
                }
            }
            else
            {
                _start = new _Node[len];
                for (int idx = 0; idx < length; idx++)
                {
#ifdef REQUIRE_TAG
                    _start[idx + M + 1].sum_content = arr[idx];
                    _start[idx + M + 1].length = 1;
                    _start[idx + M + 1].lazy_add = 0;
#ifdef REQUIRE_MULTIPLY_TAG
                    _start[idx + M + 1].lazy_mul = 1;
#endif
#ifdef REQUIRE_RMQ
                    _start[idx + M + 1].min_content = _start[idx + M + 1].max_content = _start[idx + M + 1].sum_content;
#endif
#elif defined(REQUIRE_RMQ)
                    _start[idx + M + 1].min_content = _start[idx + M + 1].max_content = arr[idx];
#endif
                }
            }

            _finish = _start + len;
            for (int idx = length + M + 1; idx < len; idx++)
            {
#ifdef REQUIRE_TAG
                _start[idx].length = 0, _start[idx].sum_content = 0;

#endif
#ifdef REQUIRE_RMQ
                _start[idx].max_content = _start[idx].min_content = 0;
#endif
            }
        }

        virtual void build() = 0;

        _Node *begin() { return _start; }
        _Node *end() { return _finish; }

        void show()
        {
            std::cout << '[';
            for (_Node *i = begin(); i != end(); i++)
                std::cout << i->sum_content << ",]"[i == end() - 1] << " \n"[i == end() - 1];
        }
    };

#ifdef REQUIRE_TAG
    template <typename T>
    struct ZKW_Tag : public ZKW_Base<T> // 带Tag型zkw线段树，常数很大，但功能比较完整
    // 只是区间加法和RMQ问题的话建议用下面的差分型
    {
        typedef ZKW_Base<T> _Base;

        using _Base::_finish;
        using _Base::_start;
        using _Base::len;
        using _Base::M;

        template <typename... Args>
        ZKW_Tag(Args &&... args) : _Base(std::forward<Args>(args)...) { build(); }
#ifdef REQUIRE_MULTIPLY_TAG

        void range_mul(int l, int r, T &v)
        {
            bool vl, vr; // 左右边第一个被访问的结点所在路径是否更新过
            vl = vr = false;
            int x;
            int sl = 0, sr = 0; // 记录左右两边第一个被访问的结点
            for (l = l + M - 1, r = r + M + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
            {
                if (~l & 1)
                {
                    x = l ^ 1;
                    if (!vl)
                    {
                        sl = x;
                        apply_tag(x);
                        vl = true; // 将第一个被访问结点所在路径的Tag更新到结点中
                    }
                    _start[x].lazy_add *= v; // 更新此次修改的tag值
                    _start[x].sum_content *= v;
                    _start[x].lazy_mul *= v;
#ifdef MODULO
                    _start[x].lazy_mul %= MODULO;
                    _start[x].sum_content %= MODULO;
                    _start[x].lazy_add %= MODULO;
#endif
                }
                if (r & 1)
                {
                    x = r ^ 1;
                    if (!vr)
                    {
                        sr = x;
                        apply_tag(x);
                        vr = true;
                    }
                    _start[x].lazy_add *= v;
                    _start[x].sum_content *= v;
                    _start[x].lazy_mul *= v;
#ifdef MODULO
                    _start[x].lazy_mul %= MODULO;
                    _start[x].sum_content %= MODULO;
                    _start[x].lazy_add %= MODULO;
#endif
                }
            }
            for (sl >>= 1; sl; sl >>= 1)
            { // 从左边开始维护
                maintain(sl);
            }
            for (sr >>= 1; sr; sr >>= 1)
            { // 从右边开始维护
                maintain(sr);
            }
        }

        void range_mul(int l, int r, T &&v)
        {
            bool vl, vr; // 左右边第一个被访问的结点所在路径是否更新过
            vl = vr = false;
            int x;
            int sl = 0, sr = 0; // 记录左右两边第一个被访问的结点
            for (l = l + M - 1, r = r + M + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
            {
                if (~l & 1)
                {
                    x = l ^ 1;
                    if (!vl)
                    {
                        sl = x;
                        apply_tag(x);
                        vl = true; // 将第一个被访问结点所在路径的Tag更新到结点中
                    }
                    _start[x].lazy_add *= v; // 更新此次修改的tag值
                    _start[x].sum_content *= v;
                    _start[x].lazy_mul *= v;
#ifdef MODULO
                    _start[x].lazy_mul %= MODULO;
                    _start[x].sum_content %= MODULO;
                    _start[x].lazy_add %= MODULO;
#endif
                }
                if (r & 1)
                {
                    x = r ^ 1;
                    if (!vr)
                    {
                        sr = x;
                        apply_tag(x);
                        vr = true;
                    }
                    _start[x].lazy_add *= v;
                    _start[x].sum_content *= v;
                    _start[x].lazy_mul *= v;
#ifdef MODULO
                    _start[x].lazy_mul %= MODULO;
                    _start[x].sum_content %= MODULO;
                    _start[x].lazy_add %= MODULO;
#endif
                }
            }
            for (sl >>= 1; sl; sl >>= 1)
            { // 从左边开始维护
                maintain(sl);
            }
            for (sr >>= 1; sr; sr >>= 1)
            { // 从右边开始维护
                maintain(sr);
            }
        }

#endif

        void range_add(int l, int r, T &v)
        {
            bool vl, vr; // 左右边第一个被访问的结点所在路径是否更新过
            vl = vr = false;
            int x;
            int sl = 0, sr = 0; // 记录左右两边第一个被访问的结点
            for (l = l + M - 1, r = r + M + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
            {
                if (~l & 1)
                {
                    x = l ^ 1;
                    if (!vl)
                    {
                        sl = x;
                        apply_tag(x);
                        vl = true; // 将第一个被访问结点所在路径的Tag更新到结点中
                    }
                    _start[x].lazy_add += v; // 更新此次修改的tag值
                    _start[x].sum_content += _start[x].length * v;
                    ; // 将当前结点的值更新
                }
                if (r & 1)
                {
                    x = r ^ 1;
                    if (!vr)
                    {
                        sr = x;
                        apply_tag(x);
                        vr = true;
                    }
                    _start[x].lazy_add += v;
                    _start[x].sum_content += _start[x].length * v;
                }
            }
            for (sl >>= 1; sl; sl >>= 1)
            { // 从左边开始维护
                maintain(sl);
            }
            for (sr >>= 1; sr; sr >>= 1)
            { // 从右边开始维护
                maintain(sr);
            }
        }

        void range_add(int l, int r, T &&v)
        {
            bool vl, vr; // 左右边第一个被访问的结点所在路径是否更新过
            vl = vr = false;
            int x;
            int sl = 0, sr = 0; // 记录左右两边第一个被访问的结点
            for (l = l + M - 1, r = r + M + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
            {
                if (~l & 1)
                {
                    x = l ^ 1;
                    if (!vl)
                    {
                        sl = x;
                        apply_tag(x);
                        vl = true; // 将第一个被访问结点所在路径的Tag更新到结点中
                    }
                    _start[x].lazy_add += v; // 更新此次修改的tag值
                    _start[x].sum_content += _start[x].length * v;
                    ; // 将当前结点的值更新
                }
                if (r & 1)
                {
                    x = r ^ 1;
                    if (!vr)
                    {
                        sr = x;
                        apply_tag(x);
                        vr = true;
                    }
                    _start[x].lazy_add += v;
                    _start[x].sum_content += _start[x].length * v;
                }
            }
            for (sl >>= 1; sl; sl >>= 1)
            { // 从左边开始维护
                maintain(sl);
            }
            for (sr >>= 1; sr; sr >>= 1)
            { // 从右边开始维护
                maintain(sr);
            }
        }

        inline void apply_tag(int x)
        {
            std::stack<int> s;
            while (x)
            { // 一路走到根结点
                s.push(x);
                x >>= 1;
            }
            while (s.size())
            { // 逐个pushDown
                push_down(s.top());
                s.pop();
            }
        }

        inline void maintain(int i)
        {
            int l = i << 1;
            int r = l | 1;
            _start[i].sum_content = (_start[l].sum_content + _start[r].sum_content)
#ifdef MODULO
                                    % MODULO
#endif
                ;
#ifdef REQUIRE_RMQ
            _start[i].max_content = max(_start[l].max_content, _start[r].max_content);
            _start[i].min_content = min(_start[l].min_content, _start[r].min_content);
#endif
        }

        inline void build()
        {
            _start[M].length = 0;
            for (int i = M - 1; i; i--)
            {
                maintain(i);
                _start[i].lazy_add = 0;
#ifdef REQUIRE_MULTIPLY_TAG
                _start[i].lazy_mul = 1;
#endif
                _start[i].length = (_start[i << 1].length + _start[i << 1 | 1].length);
            }
        }

        inline void push_down(int ind)
        {
            if (ind >= M)
                return;
            int l = ind << 1;
            int r = l | 1;
#ifdef REQUIRE_MULTIPLY_TAG
            if (_start[ind].lazy_mul != 1)
            {
                _start[l].sum_content *= _start[ind].lazy_mul;
                _start[l].sum_content += _start[ind].lazy_add * _start[l].length;
                _start[r].sum_content *= _start[ind].lazy_mul;
                _start[r].sum_content += _start[ind].lazy_add * _start[r].length;
                _start[l].lazy_mul *= _start[ind].lazy_mul;
                _start[l].lazy_add *= _start[ind].lazy_mul;
                _start[l].lazy_add += _start[ind].lazy_add;
                _start[r].lazy_mul *= _start[ind].lazy_mul;
                _start[r].lazy_add *= _start[ind].lazy_mul;
                _start[r].lazy_add += _start[ind].lazy_add;
#ifdef MODULO
                _start[l].lazy_mul %= MODULO;
                _start[l].lazy_add %= MODULO;
                _start[l].sum_content %= MODULO;
                _start[r].lazy_mul %= MODULO;
                _start[r].lazy_add %= MODULO;
                _start[r].sum_content %= MODULO;
#endif
                _start[ind].lazy_mul = 1;
                _start[ind].lazy_add = 0;
                return;
            }
#endif
            if (_start[ind].lazy_add)
            {
                _start[l].sum_content += _start[ind].lazy_add * _start[l].length;
                _start[l].lazy_add += _start[ind].lazy_add;
                _start[r].sum_content += _start[ind].lazy_add * _start[r].length;
                _start[r].lazy_add += _start[ind].lazy_add;
#ifdef MODULO
                _start[l].lazy_add %= MODULO;
                _start[l].sum_content %= MODULO;
                _start[r].lazy_add %= MODULO;
                _start[r].sum_content %= MODULO;
#endif
                _start[ind].lazy_add = 0;
            }
        }

        T query_sum(int l, int r)
        {
            bool vl = 0, vr = 0;
            T res = 0;
            // 转为开区间查询
            for (l += M - 1, r += M + 1; l ^ r ^ 1; r >>= 1, l >>= 1)
            {
                if (~l & 1)
                {
                    if (!vl)
                    {
                        vl = 1;
                        apply_tag(l ^ 1);
                    }
                    res += _start[l ^ 1].sum_content; // 若l是左儿子，加上右儿子的值，否则因为是开区间，不用算这一层的值
                }
                if (r & 1)
                {
                    if (!vr)
                    {
                        vr = 1;
                        apply_tag(r ^ 1);
                    }
                    res += _start[r ^ 1].sum_content; // 若r是右儿子，加上左儿子的值，否则因为是开区间，不用算
                }
#ifdef MODULO
                res %= MODULO;
#endif
            }
            return res;
        }
#ifdef REQUIRE_RMQ
        T query_max(int l, int r)
        {
            bool vl = 0, vr = 0;
            T res = _start[l + M].max_content;
            for (l += M - 1, r += M + 1; l ^ r ^ 1; r >>= 1, l >>= 1)
            {
                if (~l & 1)
                {
                    if (!vl)
                    {
                        vl = 1;
                        apply_tag(l ^ 1);
                    }
                    res = max(res, _start[l ^ 1].max_content);
                }
                if (r & 1)
                {
                    if (!vr)
                    {
                        vr = 1;
                        apply_tag(r ^ 1);
                    }
                    res = max(res, _start[r ^ 1].max_content);
                }
            }
            return res;
        }

        T query_min(int l, int r)
        {
            bool vl = 0, vr = 0;
            T res = _start[l + M].min_content;
            for (l += M - 1, r += M + 1; l ^ r ^ 1; r >>= 1, l >>= 1)
            {
                if (~l & 1)
                {
                    if (!vl)
                    {
                        vl = 1;
                        apply_tag(l ^ 1);
                    }
                    res = min(res, _start[l ^ 1].min_content);
                }
                if (r & 1)
                {
                    if (!vr)
                    {
                        vr = 1;
                        apply_tag(r ^ 1);
                    }
                    res = min(res, _start[r ^ 1].min_content);
                }
            }
            return res;
        }
#endif
    };
#endif

#ifdef REQUIRE_RMQ
    template <typename T>               // 类型T必须支持+= -
    struct ZKW_Dif : public ZKW_Base<T> // 差分型zkw线段树，可以处理区间加法，查询区间最值
    {
        typedef ZKW_Base<T> _Base;
        using _Base::_finish;
        using _Base::_start;
        using _Base::len;
        using _Base::M;
        template <typename... Args>
        ZKW_Dif(Args &&... args) : _Base(std::forward<Args>(args)...) { build(); } // 把当前构造函数的参数扔给父构造函数做，然后建树
        void build()
        {
            _start[M].min_content = 0;
            _start[M].max_content = 0;
            for (int i = M - 1; i > 0; i--) // 以M开始会越界，而且M的两个孩子都不是有效存储位
            {                               //build的时候用的min，则只能查区间最小值，用max则只能查最大值，这里用两个单位分开存
                _start[i].min_content = min(_start[i << 1].min_content, _start[i << 1 | 1].min_content);
                _start[i << 1].min_content -= _start[i].min_content;
                _start[i << 1 | 1].min_content -= _start[i].min_content;

                _start[i].max_content = max(_start[i << 1].max_content, _start[i << 1 | 1].max_content);
                _start[i << 1].max_content -= _start[i].max_content;
                _start[i << 1 | 1].max_content -= _start[i].max_content;
            }
        }
        void maintain(int ind)
        {
            auto L = ind << 1;
            auto R = L | 1;
            auto tmp = min(_start[L].min_content, _start[R].min_content);
            _start[L].min_content -= tmp;
            _start[R].min_content -= tmp;
            _start[ind].min_content += tmp;

            tmp = max(_start[L].max_content, _start[R].max_content);
            _start[L].max_content -= tmp;
            _start[R].max_content -= tmp;
            _start[ind].max_content += tmp;
        }

        void range_add(int l, int r, T &x)
        {
            for (l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
            {
                if (~l & 1)
                    _start[l ^ 1].min_content += x, _start[l ^ 1].max_content += x;
                if (r & 1)
                    _start[r ^ 1].min_content += x, _start[r ^ 1].max_content += x;
                maintain(l >> 1);
                maintain(r >> 1);
            }
            maintain(l);
            while (l > 1)
            {
                maintain(l >>= 1);
            }
        }                                   // 区间加法
        void range_add(int l, int r, T &&x) // 复制一份兼容右值引用
        {
            for (l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
            {
                if (~l & 1)
                    _start[l ^ 1].min_content += x, _start[l ^ 1].max_content += x;
                if (r & 1)
                    _start[r ^ 1].min_content += x, _start[r ^ 1].max_content += x;
                maintain(l >> 1);
                maintain(r >> 1);
            }
            // maintain(l);
            while (l > 1)
            {
                maintain(l >>= 1);
            }
        }
        T getval(int ind)
        {
            T res = 0;
            for (ind += M; ind; ind >>= 1)
                res += _start[ind].max_content;
            return res;
        }

        T query_min(int l, int r)
        {
            if (l == r)
                return getval(l);
            T L = 0;
            T R = 0;
            for (l += M, r += M; l ^ r ^ 1; r >>= 1, l >>= 1)
            {
                L += _start[l].min_content;
                R += _start[r].min_content;
                if (~l & 1)
                    L = min(L, _start[l ^ 1].min_content); // 若l是左儿子，用右儿子的值更新，否则因为是开区间，不用算这一层的值
                if (r & 1)
                    R = min(R, _start[r ^ 1].min_content); // 若r是右儿子，用左儿子的值更新，否则因为是开区间，不用算
            }
            L += _start[l].min_content;
            R += _start[r].min_content;
            L = min(L, R);
            while (l > 1)
                L += _start[l >>= 1].min_content;
            return L;
        }
        T query_max(int l, int r)
        {
            if (l == r)
                return getval(l);
            T L = 0;
            T R = 0;
            for (l += M, r += M; l ^ r ^ 1; r >>= 1, l >>= 1)
            {
                L += _start[l].max_content;
                R += _start[r].max_content;
                if (~l & 1)
                    L = max(L, _start[l ^ 1].max_content); // 若l是左儿子，用右儿子的值更新，否则因为是开区间，不用算这一层的值
                if (r & 1)
                    R = max(R, _start[r ^ 1].max_content); // 若r是右儿子，用左儿子的值更新，否则因为是开区间，不用算
            }
            L += _start[l].max_content; // 不能漏了l r为兄弟节点时他们的节点值
            R += _start[r].max_content;
            L = max(L, R);
            while (l > 1)                         // =1时下一行会读到0号点，而0号点是无效的并且没有初始化的信息
                L += _start[l >>= 1].max_content; // 没走到根（1号点）的话要往根走，把差分算完才能得到源信息
            return L;
        }
    };
#endif

} // namespace ZKW
#define P3373
// long long arr[8000010]; // 静态分配
// long long tree[500010];
signed main()
{
    // long long arrr[] = {1, 1, 4, 5, 1, 4, 19, 19, 810, 0};
    // ZKW::ZKW_Base<long long> f(arrr, 10);
    // f.show();
    // // for (auto i : f)
    // // std::cout << i; // 这是一般用例演示
    // std::cout << f.query_sum(1, 7);

#ifdef P3374 // 洛谷P3374的用例，原提交https://www.luogu.com.cn/record/45610579 \
             // 带tag的zkw线段树常数不小，得开O2才能过了
    int n, m;
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    for (auto i = 0; i < n; i++)
        std::cin >> tree[i]; // 直接建树开关为false时需要另外读入数组的原数据
    // ZKW::ZKW_Base<long long> f(arr, n, true);   // 指定为true会将arr的空间分配给线段树使用，arr的原来数据会被覆盖
    ZKW::ZKW_Tag<long long> f(tree, n, false); // 指定为false则根据提供的数组建树，会另外申请一块空间
    while (m--)
    {
        int arg1;
        int arg2;
        long long arg3;
        std::cin >> arg1 >> arg2 >> arg3;
        if (arg1 == 1)
            f.range_add(arg2, arg2, arg3);
        else
            std::cout << f.query_sum(arg2, arg3) << '\n';
    }
#endif

#ifdef P3368 // https://www.luogu.com.cn/record/45629213

    int n, m;
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    long long *arr = new long long[n];
    for (auto i = 0; i < n; i++)
        std::cin >> arr[i];
    // for (int i = n - 1; i >= 0; i--) // 倒序遍历的时候不建议用auto，类型推导如果推成无符号数可能形成死循环
    //     arr[i] -= arr[i - 1];
    ZKW::ZKW_Dif<long long> f(arr, n, false);
    while (m--)
    {
        int arg1;
        int arg2;
        int arg3;
        long long arg4;
        std::cin >> arg1;
        if (arg1 == 1)
        {
            std::cin >> arg2 >> arg3 >> arg4;
            f.range_add(arg2, arg3, arg4);
        }
        else
        {
            std::cin >> arg2;
            std::cout << f.query_max(arg2, arg2) << '\n';
        }
    }
#endif

#ifdef POJ3264 // POJ没有C++11，板子用不了，可以交洛谷P2880 \
               //https://www.luogu.com.cn/record/45634532
    int n, q;

    std::ios::sync_with_stdio(false);
    std::cin >> n >> q;
    long long *arr = new long long[n << 5];
    ZKW::ZKW_Dif<long long> f(arr, n, true);
    while (q--)
    {
        int l, r;
        std::cin >> l >> r;
        auto _MAX = f.query_max(l, r);
        auto _MIN = f.query_min(l, r);
        std::cout << _MAX - _MIN << '\n';
    }

#endif

#ifdef P3372 //https://www.luogu.com.cn/record/45637373
    int n, q;

    std::ios::sync_with_stdio(false);
    std::cin >> n >> q;
    long long *arr = new long long[n << 5];
    ZKW::ZKW_Tag<long long> f(arr, n, true);
    while (q--)
    {
        int cmd, l, r, val;
        std::cin >> cmd;
        if (cmd == 1)
        {
            std::cin >> l >> r >> val;
            f.range_add(l, r, val);
        }
        else
        {
            std::cin >> l >> r;
            std::cout << f.query_sum(l, r) << '\n';
        }
    }

#endif

#ifdef P3373 //https://www.luogu.com.cn/record/45638826
    int n, q;
    std::ios::sync_with_stdio(false);
    std::cin >> n >> q >> MO;
    long long *arr = new long long[n << 5];
    ZKW::ZKW_Tag<long long> f(arr, n, true);
    while (q--)
    {
        int cmd, l, r, val;
        std::cin >> cmd;
        if (cmd == 1)
        {
            std::cin >> l >> r >> val;
            f.range_mul(l, r, val);
        }
        else if (cmd == 2)
        {
            std::cin >> l >> r >> val;
            f.range_add(l, r, val);
        }
        else
        {
            std::cin >> l >> r;
            std::cout << f.query_sum(l, r) << '\n';
        }
    }
#endif

    return 0;
}