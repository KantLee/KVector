#include "kvector.hpp"
#include <iostream>

int main()
{
	KVector<int> vt;
	std::cout << "����ʼ����......" << std::endl;
	std::cout << "ʹ��Ĭ�Ϲ��캯���������ĳ�ʼԪ�ظ�����������" << std::endl;
	std::cout << "size: " << vt.size() << " capacity: " << vt.capacity() << std::endl;
	int i = 0;
	for (i = 0; i < 6; i++)
	{
		vt.push_back(i + 1);
	}

	std::cout << "\n����6��Ԫ�أ�" << std::endl;
	std::cout << "size: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\n����[]�����������vector��" << std::endl;
	for (i = 0; i < vt.size(); i++)
	{
		std::cout << vt[i] << ' ';
	}
	std::cout << std::endl;

	std::cout << "\n����at(5)�������6��Ԫ�أ�" << std::endl;
	std::cout << vt.at(5) << std::endl;

	std::cout << "\n����at(9)��Խ����ʣ������10��Ԫ�أ�" << std::endl;
	try
	{
		std::cout << vt.at(9) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\nִ��һ��pop_back��" << std::endl;
	vt.pop_back();
	std::cout << "size: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\n���������������" << std::endl;
	for (KVector<int>::iterator it = vt.begin(); it != vt.end(); it++)
	{
		std::cout << *it << ' ';
	}

	std::cout << "\n���Է����������" << std::endl;
	for (KVector<int>::reverse_iterator rit = vt.rbegin(); rit != vt.rend(); rit++)
	{
		std::cout << *rit << ' ';
	}

	std::cout << "\n\n����KVector<int>::iterator it=erase(vt.begin())��ɾ����һ��Ԫ�أ�" << std::endl;
	KVector<int>::iterator it = vt.erase(vt.begin());
	std::cout << "�Կ������صĵ�����ָ����ԭ���ĵ�2��Ԫ�أ�";
	std::cout << " *it= " << *it << std::endl;
	std::cout << "���Կ�����һ��Ԫ�ر����ԭ���ĵڶ�����vt.begin()=" << *vt.begin() << std::endl;
	for (auto it = vt.begin(); it != vt.end(); it++)
	{
		std::cout << *it << ' ';
	}
	std::cout << "\nsize: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\n����KVector<int>::iterator it=erase(vt.begin()+1,vt.end()-1)��ɾ����β֮���Ԫ�أ�" << std::endl;
	it = vt.erase(vt.begin() + 1, vt.end() - 1);
	std::cout << "���Կ���erase�������ص���ɾ�������һ��Ԫ�ص���һ��λ�ã�*it=" << *it << std::endl;
	for (auto it = vt.begin(); it != vt.end(); it++)
	{
		std::cout << *it << ' ';
	}
	std::cout << "\nsize: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\n����front��back��" << std::endl;
	std::cout << "front:" << vt.front() << " back:" << vt.back() << std::endl;

	std::cout << "\n����KVector<int>::iterator it=insert(vt.begin(),100): " << std::endl;
	it = vt.insert(vt.begin(), 100);
	std::cout << "���Կ����������ص���ָ�򱻲����Ԫ�صĵ�������*it=" << *it << std::endl;
	for (auto it = vt.begin(); it != vt.end(); it++)
	{
		std::cout << *it << ' ';
	}
	std::cout << "\nsize: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\n����reverse������20��������" << std::endl;
	vt.reserve(20);
	std::cout << "size: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\n�����Զ���С������ɾ��Ԫ�غ���������size������ʱ��������size��1.5����" << std::endl;
	vt.pop_back();
	std::cout << "size: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\n����shrink_to_fit��" << std::endl;
	vt.shrink_to_fit();
	std::cout << "size: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\n����clear��" << std::endl;
	vt.clear();
	std::cout << "size: " << vt.size() << " capacity: " << vt.capacity() << std::endl;

	std::cout << "\nKVector<int> vt_2={100,200,300,400,500},Ȼ�������" << std::endl;
	KVector<int> vt_2 = { 100,200,300,400,500 };
	for (i = 0; i < vt_2.size(); i++)
	{
		std::cout << vt_2[i] << ' ';
	}
	std::cout << std::endl << "vt2_size: " << vt_2.size() << " vt2_capacity: " << vt_2.capacity() << std::endl;

	std::cout << "\n�����µ�KVector<int> vt_3(7, 99),Ȼ�������" << std::endl;
	KVector<int> vt_3(7, 99);
	for (i = 0; i < vt_3.size(); i++)
	{
		std::cout << vt_3[i] << ' ';
	}
	std::cout << std::endl << "vt3_size: " << vt_3.size() << " vt3_capacity: " << vt_3.capacity() << std::endl;

	std::cout << "\n���Կ������캯���������µ�KVector<int> vt_4(vt_2)Ȼ�������" << std::endl;
	KVector<int> vt_4(vt_2);
	for (i = 0; i < vt_4.size(); i++)
	{
		std::cout << vt_4[i] << ' ';
	}
	std::cout << std::endl << "vt4_size: " << vt_4.size() << " vt4_capacity: " << vt_4.capacity() << std::endl;

	std::cout << "\n���Կ�����ֵ������������µ�KVector<int> vt_5=vt_3��Ȼ�������" << std::endl;
	KVector<int> vt_5 = vt_3;
	for (i = 0; i < vt_5.size(); i++)
	{
		std::cout << vt_5[i] << ' ';
	}
	std::cout << std::endl << "vt5_size: " << vt_5.size() << " vt5_capacity: " << vt_5.capacity() << std::endl;

	std::cout << "\n����swap����������vt_4��vt_5�����ݣ�" << std::endl;
	vt_5.swap(vt_4);
	std::cout << "������ϣ����vt_4�����ݺʹ�С��������" << std::endl;
	for (i = 0; i < vt_4.size(); i++)
	{
		std::cout << vt_4[i] << ' ';
	}
	std::cout << std::endl << "vt4_size: " << vt_4.size() << " vt4_capacity: " << vt_4.capacity() << std::endl;
	std::cout << "���vt_5����������ݺʹ�С��������" << std::endl;
	for (i = 0; i < vt_5.size(); i++)
	{
		std::cout << vt_5[i] << ' ';
	}
	std::cout << std::endl << "vt5_size: " << vt_5.size() << " vt5_capacity: " << vt_5.capacity() << std::endl;

	return 0;
}
