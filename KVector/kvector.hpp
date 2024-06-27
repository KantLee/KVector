// -------------------------------------------------------
// kvector.hpp
// 创建者： KantLee
// 创建时间： 2024/4/1
// 功能描述： 手写Vector
// --------------------------------------------------------
// 实现的外部接口：
// 1、operator[]、at(): 访问元素
// 2、front(), back(): 访问第一个和最后一个元素
// 3、data(): 提供对底层数组的直接访问
// 4、empty(): 检查容器是否为空
// 5、size(): 返回容器中的元素数量
// 6、reserve(): 请求改变容器容量
// 7、capacity(): 返回容器当前的容量
// 8、shrink_to_fit(): 减少容量以节省空间
// 9、erase()：删除指定或者指定范围元素
// 10、insert()：在指定位置插入元素
// 11、clear(): 清空容器内容
// 12、push_back(): 在容器末尾添加元素
// 13、pop_back(): 移除最后一个元素
// 14、swap(): 与另一个vector交换内容
// 15、提供begin(), end(), rbegin(), rend(), cbegin(), cend(), crbegin(), crend()迭代器，支持正向和反向遍历，已实现
// 16、拷贝构造函数
// 17、拷贝赋值运算符
// 18、使用vt={初始值1,初始值2...}初始化vector对象
// 19、使用vt(size,value)初始化vector对象
// 20、使用内存分配器

#ifndef _KVECTOR_KVECTOR_HPP_
#define _KVECTOR_KVECTOR_HPP_
#include <memory>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

template <typename T>
class KVector
{
public:
	explicit KVector(size_t capacity = 5);
	KVector(std::initializer_list<T> list);
	KVector(size_t cap, T value);
	KVector(const KVector& KV);	// 拷贝构造函数
	~KVector();

	// 迭代器
	using iterator = T*;
	using const_iterator = const T*;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	// 外部可调用的接口
	size_t size() const;	// 获取元素数量
	size_t capacity() const;	// 获取容量
	T &front();	// 返回第一个元素
	T &back();	// 返回最后一个元素
	T *data();	// 返回第一个元素的指针
	const T *data() const;	// 返回第一个元素的指针，常量vector使用
	void push_back(const T &value);	// 插入数据
	void pop_back();	// 移除尾部元素（不改变容量）
	bool empty();	// 检查容器是否为空
	void reserve(size_t cap);	// 分配容量
	iterator erase(iterator pos);	// 删除指定位置的函数
	iterator erase(iterator start, iterator end);	// 移除一段范围内的元素
	iterator insert(iterator pos, const T &value);	// 在指定位置插入元素
	void shrink_to_fit();	// 减少容量大小至容器元素数量
	void clear();	// 清空元素（不改变容量大小）
	void swap(KVector &KV) noexcept;	// 与另一个vector交换内容
	T &operator[](size_t index);	// 重载[]操作符
	const T &operator[](size_t index) const;	// 重载[]操作符（const）
	T &at(size_t index);	// 根据下标访问元素 
	const T &at(size_t index) const;	// 根据下标访问元素 
	KVector<T> &operator=(const KVector &KV);	// 拷贝赋值运算符

	// 定义迭代器
	iterator begin() { return m_data; }	// 返回指向第一个元素的迭代器
	iterator end() { return m_end; }	// 返回指向容器末尾的迭代器
	const_iterator begin() const { return m_data; };	// 常量迭代器，指向第一个元素
	const_iterator end() const { return m_end; };	// 常量迭代器，指向容器末尾
	const_iterator cbegin() const { return m_data; };	// 常量迭代器，指向第一个元素
	const_iterator cend() const { return m_end; };	// 常量迭代器，指向容器末尾
	reverse_iterator rbegin() { return reverse_iterator(m_end); }	// 反向迭代器，指向最后一个元素
	reverse_iterator rend() { return reverse_iterator(begin()); }	// 反向迭代器，指向第一个元素前的位置
	const_reverse_iterator crbegin() const { return const_reverse_iterator(m_end); }	// 常量反向迭代器
	const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }	// 常量反向迭代器

protected:
	void expandDoubleCapacity();	// 2倍扩容
	void assignCapacity(size_t cap);	// 重新分配空间到cap（前提是大于size）

private:
	std::allocator<T> m_alloc;
	size_t m_capacity;
	T *m_data;
	T *m_end;
};

// 默认构造函数
template<typename T>
KVector<T>::KVector(size_t capacity)
{
	this->m_capacity = capacity;
	this->m_data = this->m_alloc.allocate(capacity);	// 分配空间
	this->m_end = this->m_data;
}

// 带初始值的构造函数
template<typename T>
KVector<T>::KVector(std::initializer_list<T> list)
{
	this->m_capacity = list.size();
	this->m_data = this->m_alloc.allocate(this->m_capacity);
	this->m_end = this->m_data;
	for (const auto& item : list)
	{
		this->push_back(item);
	}
}

// 带初始容量和初始值的构造函数
template<typename T>
KVector<T>::KVector(size_t cap, T value)
{
	this->m_capacity = cap;
	this->m_data = this->m_alloc.allocate(this->m_capacity);
	this->m_end = this->m_data;
	for (size_t i = 0; i < this->m_capacity; i++)
	{
		this->push_back(value);
	}
}

// 拷贝构造函数
template<typename T>
KVector<T>::KVector(const KVector& KV)
{
	this->m_data = this->m_alloc.allocate(KV.capacity());
	// std::uninitialized_copy：在原始内存中直接构造对象
	this->m_end = std::uninitialized_copy(KV.m_data, KV.m_end, this->m_data);
	this->m_capacity = KV.capacity();
}

// 析构函数
template<typename T>
KVector<T>::~KVector()
{
	for (size_t i = 0; i < this->size(); i++)
	{
		this->m_alloc.destroy(this->m_data + i);
	}
	this->m_alloc.deallocate(this->m_data, this->m_capacity);
	this->m_data = nullptr;
	this->m_end = nullptr;
}

// 获取元素个数
template<typename T>
size_t KVector<T>::size() const
{
	return this->m_end - this->m_data;
}

// 获取容量
template<typename T>
size_t KVector<T>::capacity() const
{
	return this->m_capacity;
}

// 返回第一个元素的引用，因为可能对元素
template<typename T>
T& KVector<T>::front()
{
	return *(this->m_data);
}

// 返回最后一个元素的引用
template<typename T>
T& KVector<T>::back()
{
	return *(this->m_end - 1);
}

// 返回指向第一个元素的指针
template<typename T>
T* KVector<T>::data()
{
	return this->m_data;
}

// 返回指向第一个元素的指针，常量类型的vector使用
template<typename T>
const T* KVector<T>::data() const
{
	return this->m_data;
}

// 插入数据
template<typename T>
void KVector<T>::push_back(const T& value)
{
	if (this->size() == this->capacity())
		this->expandDoubleCapacity();	// 2倍扩容
	this->m_alloc.construct(this->m_end++, value);
}

// 删除最后一个元素
template<typename T>
void KVector<T>::pop_back()
{
	if (this->size())
	{
		this->m_alloc.destroy(--this->m_end);
		// 如果容量大于size的三倍，则减少容量到size的1.5倍
		if (this->size() * 3 < this->capacity())
			this->assignCapacity(int(this->size() * 1.5));
	}
}

// 检查容器是否为空
template<typename T>
bool KVector<T>::empty()
{
	if (this->size())
		return false;
	return true;
}

// 分配容量
template<typename T>
void KVector<T>::reserve(size_t cap)
{
	if (cap <= this->capacity())
		return;
	this->assignCapacity(cap);
}

// 移除单个元素
template<typename T>
typename KVector<T>::iterator KVector<T>::erase(iterator pos)
{
	if (pos >= this->begin() && pos < this->m_end)
	{
		// 先销毁被删除的对象
		this->m_alloc.destroy(pos);
		// 元素前移, move函数移动区间左闭右开
		std::move(pos + 1, this->m_end, pos);
		// 销毁最后的对象
		this->m_alloc.destroy(--this->m_end);
		// 如果容量大于size的三倍，则减少容量到size的1.5倍
		if (this->size() * 3 < this->capacity())
			this->assignCapacity(int(this->size() * 1.5));
		return pos;
	}
	return nullptr;
}

// 移除一段范围内的元素，区间为左闭右开
// 需要知道移动之后尾部空出来多少个未析构的元素，进行析构
template<typename T>
typename KVector<T>::iterator KVector<T>::erase(iterator start, iterator end)
{
	if (start <= end && start >= this->m_data && end <= this->m_end)
	{
		// 先销毁区间内的对象
		for (iterator it = start; it < end; it++)
		{
			this->m_alloc.destroy(it);
		}
		// 如果要删除的最后一个元素刚好是最后一个对象，就不用往前move了
		if (end == this->m_end)
		{
			this->m_end = start;
		}
		else
		{
			std::move(end, this->m_end, start);
			// 销毁往前move之后结尾空出来的元素
			for (iterator it = this->m_end - end + start; it < this->m_end; it++)
			{
				this->m_alloc.destroy(it);
			}
			// 设置尾指针的位置
			this->m_end = this->m_end - end + start;
		}
		// 如果容量大于size的三倍，则减少容量到size的1.5倍
		if (this->size() * 3 < this->capacity())
			this->assignCapacity(int(this->size() * 1.5));
		return start;
	}
	return nullptr;
}

// 在指定位置插入元素
template<typename T>
typename KVector<T>::iterator KVector<T>::insert(iterator pos, const T& value)
{
	if (pos >= this->m_data && pos <= this->m_end)
	{
		// 如果size()==capacity()，则进行二倍扩容
		if (this->capacity() == this->size())
			this->expandDoubleCapacity();
		if (pos == this->m_end)
		{
			// 如果刚好在结尾插入，就不用移动了
			this->m_alloc.construct(this->m_end, value);
		}
		else
		{
			std::move(pos, this->m_end, pos + 1);
			// 先销毁原来的对象，因为现在是不确定的状态
			this->m_alloc.destroy(pos);
			// 销毁完毕再插入新元素
			this->m_alloc.construct(pos, value);
		}
		this->m_end++;
		return pos;
	}
	return nullptr;
}

// 减少容量大小至容器元素数量
template<typename T>
void KVector<T>::shrink_to_fit()
{
	if (this->capacity() <= this->size())
		return;
	this->assignCapacity(this->size());
}

// 清空元素
template<typename T>
void KVector<T>::clear()
{
	if (this->size() == 0)
	{
		return;
	}
	size_t now_size = this->size();
	for (size_t i = 0; i < now_size; i++)
	{
		this->m_alloc.destroy(--this->m_end);
	}
}

// 与另一个vector交换内容
// noexcept，保证不抛出异常，即使在内存紧张的情况下，操作也能安全进行
template<typename T>
void KVector<T>::swap(KVector& KV) noexcept
{
	// 确保如果命名空间中存在针对当前类型的 swap 函数，则优先使用
	using std::swap;
	swap(this->m_data, KV.m_data);
	swap(this->m_end, KV.m_end);
	swap(this->m_capacity, KV.m_capacity);
}

// 重载[]符号
template<typename T>
T& KVector<T>::operator[](size_t index)
{
	return this->m_data[index];
}

template<typename T>
const T& KVector<T>::operator[](size_t index) const
{
	return this->m_data[index];
}

// 根据下标访问元素，与[]不同的是，访问的下标越界会抛出异常
template<typename T>
T& KVector<T>::at(size_t index)
{
	if (0 <= index && index < this->size())
		return this->m_data[index];
	else
		throw std::out_of_range("Index out of range");	// 抛出异常
}

// 根据下标访问元素，常量类型
template<typename T>
const T& KVector<T>::at(size_t index) const
{
	if (0 <= index && index < this->size())
		return this->m_data[index];
	else
		throw std::out_of_range("Index out of range");	// 抛出异常
}

// 重载=运算符
template<typename T>
KVector<T>& KVector<T>::operator=(const KVector& KV)
{
	KVector temp(KV);
	this->swap(temp);
	return *this;
}

// 2倍扩容
template<typename T>
void KVector<T>::expandDoubleCapacity()
{
	bool capZero = false;
	if (this->m_capacity == 0)
	{
		this->m_capacity = 1;	// 如果容量为0，先初始化为1
		capZero = true;
	}
	// 分配新空间，大小为原来的2倍
	T* newData = this->m_alloc.allocate(this->m_capacity * 2);
	T* newEnd = newData;
	for (size_t i = 0; i < this->size(); i++)
	{
		// 移动元素到新空间
		this->m_alloc.construct(newEnd++, std::move(*(this->m_data + i)));
	}
	for (size_t i = 0; i < this->size(); i++)
	{
		this->m_alloc.destroy(this->m_data + i);	// 销毁原来空间上的对象
	}
	// 释放原来空间内存
	if (capZero)
		// 因为如果最开始容量为0时，人为的将容量扩展了，这里需要释放原来的
		this->m_alloc.deallocate(this->m_data, 0);
	else
		this->m_alloc.deallocate(this->m_data, this->m_capacity);
	// 另m_data和m_end指向新的空间
	this->m_data = newData;
	this->m_end = newEnd;
	this->m_capacity *= 2;
}

// 重新分配空间到cap（前提是大于size）
template<typename T>
void KVector<T>::assignCapacity(size_t cap)
{
	// 申请新空间，大小为cap
	T* newData = this->m_alloc.allocate(cap);
	T* newEnd = newData;
	for (size_t i = 0; i < this->size(); i++)
	{
		// 移动原来的数据到新空间
		this->m_alloc.construct(newEnd++, std::move(*(this->m_data + i)));
	}
	for (size_t i = 0; i < this->size(); i++)
	{
		// 删除原来的元素对象
		this->m_alloc.destroy(this->m_data + i);
	}
	// 释放内存
	this->m_alloc.deallocate(this->m_data, this->m_capacity);
	this->m_data = newData;
	this->m_end = newEnd;
	this->m_capacity = cap;
}

#endif	// _KVECTOR_KVECTOR_HPP_
