// -------------------------------------------------------
// kvector.hpp
// �����ߣ� KantLee
// ����ʱ�䣺 2024/4/1
// ���������� ��дVector
// --------------------------------------------------------
// ʵ�ֵ��ⲿ�ӿڣ�
// 1��operator[]��at(): ����Ԫ��
// 2��front(), back(): ���ʵ�һ�������һ��Ԫ��
// 3��data(): �ṩ�Եײ������ֱ�ӷ���
// 4��empty(): ��������Ƿ�Ϊ��
// 5��size(): ���������е�Ԫ������
// 6��reserve(): ����ı���������
// 7��capacity(): ����������ǰ������
// 8��shrink_to_fit(): ���������Խ�ʡ�ռ�
// 9��erase()��ɾ��ָ������ָ����ΧԪ��
// 10��insert()����ָ��λ�ò���Ԫ��
// 11��clear(): �����������
// 12��push_back(): ������ĩβ���Ԫ��
// 13��pop_back(): �Ƴ����һ��Ԫ��
// 14��swap(): ����һ��vector��������
// 15���ṩbegin(), end(), rbegin(), rend(), cbegin(), cend(), crbegin(), crend()��������֧������ͷ����������ʵ��
// 16���������캯��
// 17��������ֵ�����
// 18��ʹ��vt={��ʼֵ1,��ʼֵ2...}��ʼ��vector����
// 19��ʹ��vt(size,value)��ʼ��vector����
// 20��ʹ���ڴ������

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
	KVector(const KVector& KV);	// �������캯��
	~KVector();

	// ������
	using iterator = T*;
	using const_iterator = const T*;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	// �ⲿ�ɵ��õĽӿ�
	size_t size() const;	// ��ȡԪ������
	size_t capacity() const;	// ��ȡ����
	T &front();	// ���ص�һ��Ԫ��
	T &back();	// �������һ��Ԫ��
	T *data();	// ���ص�һ��Ԫ�ص�ָ��
	const T *data() const;	// ���ص�һ��Ԫ�ص�ָ�룬����vectorʹ��
	void push_back(const T &value);	// ��������
	void pop_back();	// �Ƴ�β��Ԫ�أ����ı�������
	bool empty();	// ��������Ƿ�Ϊ��
	void reserve(size_t cap);	// ��������
	iterator erase(iterator pos);	// ɾ��ָ��λ�õĺ���
	iterator erase(iterator start, iterator end);	// �Ƴ�һ�η�Χ�ڵ�Ԫ��
	iterator insert(iterator pos, const T &value);	// ��ָ��λ�ò���Ԫ��
	void shrink_to_fit();	// ����������С������Ԫ������
	void clear();	// ���Ԫ�أ����ı�������С��
	void swap(KVector &KV) noexcept;	// ����һ��vector��������
	T &operator[](size_t index);	// ����[]������
	const T &operator[](size_t index) const;	// ����[]��������const��
	T &at(size_t index);	// �����±����Ԫ�� 
	const T &at(size_t index) const;	// �����±����Ԫ�� 
	KVector<T> &operator=(const KVector &KV);	// ������ֵ�����

	// ���������
	iterator begin() { return m_data; }	// ����ָ���һ��Ԫ�صĵ�����
	iterator end() { return m_end; }	// ����ָ������ĩβ�ĵ�����
	const_iterator begin() const { return m_data; };	// ������������ָ���һ��Ԫ��
	const_iterator end() const { return m_end; };	// ������������ָ������ĩβ
	const_iterator cbegin() const { return m_data; };	// ������������ָ���һ��Ԫ��
	const_iterator cend() const { return m_end; };	// ������������ָ������ĩβ
	reverse_iterator rbegin() { return reverse_iterator(m_end); }	// �����������ָ�����һ��Ԫ��
	reverse_iterator rend() { return reverse_iterator(begin()); }	// �����������ָ���һ��Ԫ��ǰ��λ��
	const_reverse_iterator crbegin() const { return const_reverse_iterator(m_end); }	// �������������
	const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }	// �������������

protected:
	void expandDoubleCapacity();	// 2������
	void assignCapacity(size_t cap);	// ���·���ռ䵽cap��ǰ���Ǵ���size��

private:
	std::allocator<T> m_alloc;
	size_t m_capacity;
	T *m_data;
	T *m_end;
};

// Ĭ�Ϲ��캯��
template<typename T>
KVector<T>::KVector(size_t capacity)
{
	this->m_capacity = capacity;
	this->m_data = this->m_alloc.allocate(capacity);	// ����ռ�
	this->m_end = this->m_data;
}

// ����ʼֵ�Ĺ��캯��
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

// ����ʼ�����ͳ�ʼֵ�Ĺ��캯��
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

// �������캯��
template<typename T>
KVector<T>::KVector(const KVector& KV)
{
	this->m_data = this->m_alloc.allocate(KV.capacity());
	// std::uninitialized_copy����ԭʼ�ڴ���ֱ�ӹ������
	this->m_end = std::uninitialized_copy(KV.m_data, KV.m_end, this->m_data);
	this->m_capacity = KV.capacity();
}

// ��������
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

// ��ȡԪ�ظ���
template<typename T>
size_t KVector<T>::size() const
{
	return this->m_end - this->m_data;
}

// ��ȡ����
template<typename T>
size_t KVector<T>::capacity() const
{
	return this->m_capacity;
}

// ���ص�һ��Ԫ�ص����ã���Ϊ���ܶ�Ԫ��
template<typename T>
T& KVector<T>::front()
{
	return *(this->m_data);
}

// �������һ��Ԫ�ص�����
template<typename T>
T& KVector<T>::back()
{
	return *(this->m_end - 1);
}

// ����ָ���һ��Ԫ�ص�ָ��
template<typename T>
T* KVector<T>::data()
{
	return this->m_data;
}

// ����ָ���һ��Ԫ�ص�ָ�룬�������͵�vectorʹ��
template<typename T>
const T* KVector<T>::data() const
{
	return this->m_data;
}

// ��������
template<typename T>
void KVector<T>::push_back(const T& value)
{
	if (this->size() == this->capacity())
		this->expandDoubleCapacity();	// 2������
	this->m_alloc.construct(this->m_end++, value);
}

// ɾ�����һ��Ԫ��
template<typename T>
void KVector<T>::pop_back()
{
	if (this->size())
	{
		this->m_alloc.destroy(--this->m_end);
		// �����������size�������������������size��1.5��
		if (this->size() * 3 < this->capacity())
			this->assignCapacity(int(this->size() * 1.5));
	}
}

// ��������Ƿ�Ϊ��
template<typename T>
bool KVector<T>::empty()
{
	if (this->size())
		return false;
	return true;
}

// ��������
template<typename T>
void KVector<T>::reserve(size_t cap)
{
	if (cap <= this->capacity())
		return;
	this->assignCapacity(cap);
}

// �Ƴ�����Ԫ��
template<typename T>
typename KVector<T>::iterator KVector<T>::erase(iterator pos)
{
	if (pos >= this->begin() && pos < this->m_end)
	{
		// �����ٱ�ɾ���Ķ���
		this->m_alloc.destroy(pos);
		// Ԫ��ǰ��, move�����ƶ���������ҿ�
		std::move(pos + 1, this->m_end, pos);
		// �������Ķ���
		this->m_alloc.destroy(--this->m_end);
		// �����������size�������������������size��1.5��
		if (this->size() * 3 < this->capacity())
			this->assignCapacity(int(this->size() * 1.5));
		return pos;
	}
	return nullptr;
}

// �Ƴ�һ�η�Χ�ڵ�Ԫ�أ�����Ϊ����ҿ�
// ��Ҫ֪���ƶ�֮��β���ճ������ٸ�δ������Ԫ�أ���������
template<typename T>
typename KVector<T>::iterator KVector<T>::erase(iterator start, iterator end)
{
	if (start <= end && start >= this->m_data && end <= this->m_end)
	{
		// �����������ڵĶ���
		for (iterator it = start; it < end; it++)
		{
			this->m_alloc.destroy(it);
		}
		// ���Ҫɾ�������һ��Ԫ�ظպ������һ�����󣬾Ͳ�����ǰmove��
		if (end == this->m_end)
		{
			this->m_end = start;
		}
		else
		{
			std::move(end, this->m_end, start);
			// ������ǰmove֮���β�ճ�����Ԫ��
			for (iterator it = this->m_end - end + start; it < this->m_end; it++)
			{
				this->m_alloc.destroy(it);
			}
			// ����βָ���λ��
			this->m_end = this->m_end - end + start;
		}
		// �����������size�������������������size��1.5��
		if (this->size() * 3 < this->capacity())
			this->assignCapacity(int(this->size() * 1.5));
		return start;
	}
	return nullptr;
}

// ��ָ��λ�ò���Ԫ��
template<typename T>
typename KVector<T>::iterator KVector<T>::insert(iterator pos, const T& value)
{
	if (pos >= this->m_data && pos <= this->m_end)
	{
		// ���size()==capacity()������ж�������
		if (this->capacity() == this->size())
			this->expandDoubleCapacity();
		if (pos == this->m_end)
		{
			// ����պ��ڽ�β���룬�Ͳ����ƶ���
			this->m_alloc.construct(this->m_end, value);
		}
		else
		{
			std::move(pos, this->m_end, pos + 1);
			// ������ԭ���Ķ�����Ϊ�����ǲ�ȷ����״̬
			this->m_alloc.destroy(pos);
			// ��������ٲ�����Ԫ��
			this->m_alloc.construct(pos, value);
		}
		this->m_end++;
		return pos;
	}
	return nullptr;
}

// ����������С������Ԫ������
template<typename T>
void KVector<T>::shrink_to_fit()
{
	if (this->capacity() <= this->size())
		return;
	this->assignCapacity(this->size());
}

// ���Ԫ��
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

// ����һ��vector��������
// noexcept����֤���׳��쳣����ʹ���ڴ���ŵ�����£�����Ҳ�ܰ�ȫ����
template<typename T>
void KVector<T>::swap(KVector& KV) noexcept
{
	// ȷ����������ռ��д�����Ե�ǰ���͵� swap ������������ʹ��
	using std::swap;
	swap(this->m_data, KV.m_data);
	swap(this->m_end, KV.m_end);
	swap(this->m_capacity, KV.m_capacity);
}

// ����[]����
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

// �����±����Ԫ�أ���[]��ͬ���ǣ����ʵ��±�Խ����׳��쳣
template<typename T>
T& KVector<T>::at(size_t index)
{
	if (0 <= index && index < this->size())
		return this->m_data[index];
	else
		throw std::out_of_range("Index out of range");	// �׳��쳣
}

// �����±����Ԫ�أ���������
template<typename T>
const T& KVector<T>::at(size_t index) const
{
	if (0 <= index && index < this->size())
		return this->m_data[index];
	else
		throw std::out_of_range("Index out of range");	// �׳��쳣
}

// ����=�����
template<typename T>
KVector<T>& KVector<T>::operator=(const KVector& KV)
{
	KVector temp(KV);
	this->swap(temp);
	return *this;
}

// 2������
template<typename T>
void KVector<T>::expandDoubleCapacity()
{
	bool capZero = false;
	if (this->m_capacity == 0)
	{
		this->m_capacity = 1;	// �������Ϊ0���ȳ�ʼ��Ϊ1
		capZero = true;
	}
	// �����¿ռ䣬��СΪԭ����2��
	T* newData = this->m_alloc.allocate(this->m_capacity * 2);
	T* newEnd = newData;
	for (size_t i = 0; i < this->size(); i++)
	{
		// �ƶ�Ԫ�ص��¿ռ�
		this->m_alloc.construct(newEnd++, std::move(*(this->m_data + i)));
	}
	for (size_t i = 0; i < this->size(); i++)
	{
		this->m_alloc.destroy(this->m_data + i);	// ����ԭ���ռ��ϵĶ���
	}
	// �ͷ�ԭ���ռ��ڴ�
	if (capZero)
		// ��Ϊ����ʼ����Ϊ0ʱ����Ϊ�Ľ�������չ�ˣ�������Ҫ�ͷ�ԭ����
		this->m_alloc.deallocate(this->m_data, 0);
	else
		this->m_alloc.deallocate(this->m_data, this->m_capacity);
	// ��m_data��m_endָ���µĿռ�
	this->m_data = newData;
	this->m_end = newEnd;
	this->m_capacity *= 2;
}

// ���·���ռ䵽cap��ǰ���Ǵ���size��
template<typename T>
void KVector<T>::assignCapacity(size_t cap)
{
	// �����¿ռ䣬��СΪcap
	T* newData = this->m_alloc.allocate(cap);
	T* newEnd = newData;
	for (size_t i = 0; i < this->size(); i++)
	{
		// �ƶ�ԭ�������ݵ��¿ռ�
		this->m_alloc.construct(newEnd++, std::move(*(this->m_data + i)));
	}
	for (size_t i = 0; i < this->size(); i++)
	{
		// ɾ��ԭ����Ԫ�ض���
		this->m_alloc.destroy(this->m_data + i);
	}
	// �ͷ��ڴ�
	this->m_alloc.deallocate(this->m_data, this->m_capacity);
	this->m_data = newData;
	this->m_end = newEnd;
	this->m_capacity = cap;
}

#endif	// _KVECTOR_KVECTOR_HPP_
