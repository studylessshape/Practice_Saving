/* 
 * 凡路游戏部作业 List
 * 简述：实现下面的IList接口，完成一个数据结构，实现可变长度数组
 * 一开始默认长度为8，提供一个指定初始Count的构造方法和一个无参构造方法
 * 当Insert的时候Count超过了Capacity时，Capacity翻倍
 * 作者：WJL
 * 版权所有，翻版不究
 */
namespace Final.FKGame.Study._001_List
{
    public interface IList<T>
    {
        /// <summary>
        /// 存放数据数量
        /// </summary>
        int Count { get; set; }

        /// <summary>
        /// List 最大容量
        /// </summary>
        int Capacity { get; }

        /// <summary>
        /// 提供读取和编辑列表中的项的方法
        /// </summary>
        T this[int index] { get; set; }

        /// <summary>
        /// 搜索指定的对象，并返回第一个匹配项的索引
        /// 如果项不在列表中，返回-1
        /// </summary>
        int IndexOf(T value);

        /// <summary>
        /// 插入一个值到列表末尾
        /// </summary>
        void Add(T value);

        /// <summary>
        /// 移除索引位置的项，其他项向前填补空缺
        /// </summary>
        void RemoveAt(int index);

        /// <summary>
        /// 使用默认比较器对所有元素进行排序
        /// </summary>
        void Sort();
    }
}