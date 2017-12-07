#ifndef __STRING_H__
#define __STRING_H__

class String {
public:
	String(const char* str = NULL);					// 普通构造函数    
	String(const String& other);					// 拷贝构造函数
	~String();								        // 析构函数    
	String& operator=(const String& other);         // 赋值函数
private:
	char* m_data;									// 用于保存字符串
};

String::String(const char* str) {
	// 传入参数为空
	if (str == nullptr) {
		m_data = new char[1]; // 需为'\0'申请一个字节的空间
		*m_data = '\0';
	}
	else {
		int len = strlen(str);
		m_data = new char[len + 1];
		strcpy(this->m_data, str);	
	}
}

String::String(const String& other) {
	// 拷贝构造函数用于初始化，所以没有删除已有空间的问题
	int len = strlen(other.m_data);
	m_data = new char[len + 1];
	strcpy(m_data, other.m_data);
}

String::~String() {
	// 注意成对使用new/delete和new[]/delete[]
	delete[] m_data;
}


String& String::operator=(const String& other) {
	// 拷贝构造函数用于初始化，而赋值运算符用于赋值（被赋值对象已经被创建）
	
	// 1、自我赋值
	if (this == &other) {
		return *this;
	}
	// 2、删除原有对象的后（避免内存泄漏）再进行动态分配
	delete[] m_data;
	int len = strlen(other.m_data);
	m_data = new char[len + 1];
	strcpy(m_data, other.m_data);

	// 3、返回*this
	return *this;
}

#endif // !__STRING_H__


