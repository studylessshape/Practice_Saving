using System;
using System.Collections;
using System.Collections.Generic;

namespace Final.FKGame.Study._001_List
{
    public class OwnList<T> : IList<T>
    {
        public T this[int index]
        {
            get
            {
                if (index >= 0 && index <= Count - 1)
                {
                    return array[index];
                }
                else
                {
                    throw new Exception("Index out of range!");
                }
                
            }
            set
            {
                if (index >= 0 && index <= Count - 1)
                {
                    array[index] = value;
                }
                else
                {
                    throw new Exception("Index out of range!");
                }
            }
        }
        private T[] array;
        private int count = 0;
        public OwnList()
        {
            array = new T[0];
        }

        public OwnList(int capacity)
        {
            if (capacity >= 0)
            {
                array = new T[capacity];
            }
            else
            {
                throw new Exception("Wrong Capacity!");
            }
        }

        public int Count { get { return count; } set { count = value; } }

        public int Capacity { get { return array.Length; } }

        public int IndexOf(T value)
        {
            for (int i = 0; i < Count; i++)
            {
                if (object.Equals(value, array[i]))
                {
                    return i;
                }
            }

            return -1;
        }
        public int LastIndexOf(T value)
        {
            for (int i = Count - 1; i >= 0; i--)
            {
                if (object.Equals(value, array[i]))
                {
                    return i;
                }
            }

            return -1;
        }
        public void Add(T value)
        {
            if (Count == Capacity)
            {
                if (Capacity == 0)
                {
                    array = new T[8];
                }
                else
                {
                    T[] newArray = new T[Capacity * 2];
                    Array.Copy(array, newArray, Count);
                    array = newArray;
                }
            }

            array[Count] = value;
            Count++;
        }

        public void RemoveAt(int index)
        {
            if (index >= 0 && index <= Count - 1)
            {
                //List`1.cs中的原生移除方法
                //Array.Copy((Array)array, index + 1, (Array)array, index , Count - index);
                
                //普通方法
                for (int i = index + 1; i < Count; i++)
                {
                    array[i - 1] = array[i];
                }
                count--;
            }
            else
            {
                throw new Exception("Index out of range!");
            }
            
        }

        public void Insert(int index, T value)
        {
            if (index >= 0 && index <= Count - 1)
            {
                if (Count == Capacity)
                {
                    T[] newArray = new T[Capacity * 2];
                    Array.Copy(array, newArray, Count);
                    array = newArray;
                }

                for (int i = Count - 1; i >= index; i--)
                {
                    array[i + 1] = array[i];
                }

                count++;
                array[index] = value;
            }
            else
            {
                throw new Exception("Index out of range!");
            }
        }

        public void Sort()
        {
            int j;
            T temp;
            for (int i = 0; i < Count; i++)
            {
                j = i;
                for (int k = i + 1; k < Count; k++)
                {
                    if (array[j].GetHashCode() > array[k].GetHashCode())
                    {
                        j = k;
                    }
                }

                if (j != i)
                {
                    temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    }
}
