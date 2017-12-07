#ifndef __SHARED_PTR_H__
#define __SHARED_PTR_H__

/*一般来说，智能指针的实现需要以下步骤：

1.一个模板指针T* ptr，指向实际的对象。

2.一个引用次数(必须new出来的，不然会多个shared_ptr里面会有不同的引用次数而导致多次delete)。

3.重载operator*和operator->，使得能像指针一样使用shared_ptr。

4.重载copy constructor，使其引用次数加一。

5.重载operator = ，如果原来的shared_ptr已经有对象，则让其引用次数减一并判断引用是否为零(是否调用delete)。

然后将新的对象引用次数加一。

6.重载析构函数，使引用次数减一并判断引用是否为零(是否调用delete)。
参考：https://www.cnblogs.com/runnyu/p/5822304.html
*/

template <typename T>
class shared_ptr
{
public:
	shared_ptr(T* p) :_count(new int(1)), _ptr(p) {}
	shared_ptr(shared_ptr<T>& other) :_count(&(++*other._count)), _ptr(other._ptr) {}
	shared_ptr<T>& operator=(shared_ptr<T>& other) {
		++*other._count;
		if (this->_ptr && 0 == --*this->_count) {
			delete _count;
			delete _ptr;
		}
		this->_ptr = other._ptr;
		this->_count = other._count;

		return *this;
	}
	~shared_ptr() {
		if (--*_count == 0) {
			delete _count;
			delete _ptr;
		}
	}

	int getRef() {
		return *_count;
	}
private:
	int* _count;
	T* _ptr;
};

#endif // !__SHARED_PTR_H__

