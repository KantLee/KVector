#include "kvector.hpp"
#include <iostream>

int main()
{
	KVector<int> vt;
	std::cout << "程序开始运行......" << std::endl;
	std::cout << "使用默认构造函数，容器的初始元素个数和容量：" << std::endl;
	std::cout << "size: " << vt.size() << " capacity: " << vt.capacity() << std::endl;
	int i = 0;
	for (i = 0; i < 6; i++)
	{
		vt.push_back(i + 1);
	}

	std::cout << "\n插入6个元素：" << std::endl;
	std::cout << "size: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\n测试[]运算符，遍历vector：" << std::endl;
	for (i = 0; i < vt.size(); i++)
	{
		std::cout << vt[i] << ' ';
	}
	std::cout << std::endl;

	std::cout << "\n测试at(5)，输出第6个元素：" << std::endl;
	std::cout << vt.at(5) << std::endl;

	std::cout << "\n测试at(9)的越界访问，输出第10个元素：" << std::endl;
	try
	{
		std::cout << vt.at(9) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n执行一次pop_back：" << std::endl;
	vt.pop_back();
	std::cout << "size: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\n测试正向迭代器：" << std::endl;
	for (KVector<int>::iterator it = vt.begin(); it != vt.end(); it++)
	{
		std::cout << *it << ' ';
	}

	std::cout << "\n测试反向迭代器：" << std::endl;
	for (KVector<int>::reverse_iterator rit = vt.rbegin(); rit != vt.rend(); rit++)
	{
		std::cout << *rit << ' ';
	}

	std::cout << "\n\n测试KVector<int>::iterator it=erase(vt.begin())，删除第一个元素：" << std::endl;
	KVector<int>::iterator it = vt.erase(vt.begin());
	std::cout << "以看到返回的迭代器指向了原来的第2个元素：";
	std::cout << " *it= " << *it << std::endl;
	std::cout << "可以看到第一个元素变成了原来的第二个：vt.begin()=" << *vt.begin() << std::endl;
	for (auto it = vt.begin(); it != vt.end(); it++)
	{
		std::cout << *it << ' ';
	}
	std::cout << "\nsize: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\n测试KVector<int>::iterator it=erase(vt.begin()+1,vt.end()-1)，删除首尾之间的元素：" << std::endl;
	it = vt.erase(vt.begin() + 1, vt.end() - 1);
	std::cout << "可以看到erase函数返回的是删除的最后一个元素的下一个位置，*it=" << *it << std::endl;
	for (auto it = vt.begin(); it != vt.end(); it++)
	{
		std::cout << *it << ' ';
	}
	std::cout << "\nsize: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\n测试front和back：" << std::endl;
	std::cout << "front:" << vt.front() << " back:" << vt.back() << std::endl;

	std::cout << "\n测试KVector<int>::iterator it=insert(vt.begin(),100): " << std::endl;
	it = vt.insert(vt.begin(), 100);
	std::cout << "可以看到函数返回的是指向被插入的元素的迭代器，*it=" << *it << std::endl;
	for (auto it = vt.begin(); it != vt.end(); it++)
	{
		std::cout << *it << ' ';
	}
	std::cout << "\nsize: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\n测试reverse，分配20个容量：" << std::endl;
	vt.reserve(20);
	std::cout << "size: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\n测试自动缩小容量，删除元素后当容量大于size的三倍时，收缩至size的1.5倍：" << std::endl;
	vt.pop_back();
	std::cout << "size: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\n测试shrink_to_fit：" << std::endl;
	vt.shrink_to_fit();
	std::cout << "size: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\n测试clear：" << std::endl;
	vt.clear();
	std::cout << "size: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\nKVector<int> vt_2={100,200,300,400,500},然后遍历：" << std::endl;
	KVector<int> vt_2 = { 100,200,300,400,500 };
	for (i = 0; i < vt_2.size(); i++)
	{
		std::cout << vt_2[i] << ' ';
	}
	std::cout << std::endl << "vt2_size: " << vt_2.size() << " vt2_capacity: " << vt_2.capacity() << std::endl;

	std::cout << "\n创建新的KVector<int> vt_3(7, 99),然后遍历：" << std::endl;
	KVector<int> vt_3(7, 99);
	for (i = 0; i < vt_3.size(); i++)
	{
		std::cout << vt_3[i] << ' ';
	}
	std::cout << std::endl << "vt3_size: " << vt_3.size() << " vt3_capacity: " << vt_3.capacity() << std::endl;

	std::cout << "\n测试拷贝构造函数，创建新的KVector<int> vt_4(vt_2)然后遍历：" << std::endl;
	KVector<int> vt_4(vt_2);
	for (i = 0; i < vt_4.size(); i++)
	{
		std::cout << vt_4[i] << ' ';
	}
	std::cout << std::endl << "vt4_size: " << vt_4.size() << " vt4_capacity: " << vt_4.capacity() << std::endl;

	std::cout << "\n测试拷贝赋值运算符，创建新的KVector<int> vt_5=vt_3，然后遍历：" << std::endl;
	KVector<int> vt_5 = vt_3;
	for (i = 0; i < vt_5.size(); i++)
	{
		std::cout << vt_5[i] << ' ';
	}
	std::cout << std::endl << "vt5_size: " << vt_5.size() << " vt5_capacity: " << vt_5.capacity() << std::endl;

	std::cout << "\n测试swap函数，交换vt_4和vt_5的内容：" << std::endl;
	vt_5.swap(vt_4);
	std::cout << "交换完毕，输出vt_4的数据和大小、容量：" << std::endl;
	for (i = 0; i < vt_4.size(); i++)
	{
		std::cout << vt_4[i] << ' ';
	}
	std::cout << std::endl << "vt4_size: " << vt_4.size() << " vt4_capacity: " << vt_4.capacity() << std::endl;
	std::cout << "输出vt_5交换后的数据和大小、容量：" << std::endl;
	for (i = 0; i < vt_5.size(); i++)
	{
		std::cout << vt_5[i] << ' ';
	}
	std::cout << std::endl << "vt5_size: " << vt_5.size() << " vt5_capacity: " << vt_5.capacity() << std::endl;

	return 0;
}
