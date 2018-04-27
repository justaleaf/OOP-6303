#include <memory>
#include <iostream>
#include <functional>
#include <string>
#include <stdexcept>
#include <utility>
#include <cstddef>
namespace stepik
{
	template<typename T>
	class shared_ptr
	{
		T *m_pointer;
		long *m_count;
		void release()
		{
			if (m_pointer)
			{
				(*m_count)--;
				if (!(*m_count))
				{
					delete m_pointer;
					delete m_count;
				}
			}
		}
	public:
		explicit shared_ptr(T *ptr = nullptr) : m_pointer(ptr),
			m_count(ptr ? new long(1) : 0) {}

		~shared_ptr()
		{
			release();
		}

		shared_ptr(const shared_ptr &other)
		{
			m_pointer = other.m_pointer;
			m_count = other.m_count;
			if (other.m_count)
				(*m_count)++;
		}

		template<typename U>
		shared_ptr(const shared_ptr<U> &other)
		{
			try
			{
				m_pointer = dynamic_cast<T *>(other.get());
			}
			catch (std::bad_cast &ex)
			{
				throw ex;
			}
			m_count = other.get_count();
			if (m_count)
				(*m_count)++;
		}

		shared_ptr &operator=(const shared_ptr &other)
		{
			if (this != &other)
			{
				release();
				m_pointer = other.get();
				m_count = other.m_count;
				if (m_count)
					(*m_count)++;
			}
			return *this;
		}

		template<typename U>
		shared_ptr &operator=(const shared_ptr<U> &other)
		{
			release();
			try
			{
				m_pointer = dynamic_cast<T *>(other.get());
			}
			catch (std::bad_cast &ex)
			{
				throw ex;
			}
			m_count = other.get_count();
			if (m_count)
				(*m_count)++;
			return *this;
		}

		explicit operator bool() const
		{
			return (m_pointer != nullptr);
		}

		T *get() const
		{
			return m_pointer;
		}

		long *get_count() const
		{
			return m_count;
		}

		long use_count() const
		{
			if (m_pointer)
				return *m_count;
			return 0;
		}

		T &operator*() const
		{
			return *m_pointer;
		}

		T *operator->() const
		{
			return m_pointer;
		}

		void swap(shared_ptr &x) noexcept
		{
			std::swap(m_count, x.m_count);
			std::swap(m_pointer, x.m_pointer);
		}

		void reset(T *ptr = nullptr)
		{
			release();
			m_pointer = ptr;
			m_count = ptr ? new long(1) : 0;
		}
	};

	template<typename T, typename U>
	bool operator==(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return (lhs.get() == rhs.get());
	}

	template <typename T>
	bool operator==(const shared_ptr<T>& lhs, nullptr_t) noexcept
	{
		return !lhs.get();
	}

	template <typename T>
	bool operator==(nullptr_t, const shared_ptr<T>& rhs) noexcept
	{
		return !rhs.get();
	}

	template< typename T, typename U >
	bool operator!=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return !(lhs.get() == rhs.get());
	}

	template <typename T>
	bool operator!=(const shared_ptr<T>& lhs, nullptr_t) noexcept
	{
		return (bool)lhs;
	}

	template <typename T>
	bool operator!=(nullptr_t, const shared_ptr<T>& rhs) noexcept
	{
		return (bool)rhs;
	}

	template <typename T, typename U>
	bool operator<(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return std::less<void *>()(static_cast<void *>(lhs.get()), static_cast<void *>(rhs.get()));
	}

	template <typename T>
	bool operator<(nullptr_t, const shared_ptr<T>& rhs) noexcept
	{
		return std::less<T *>()(nullptr, rhs.get());
	}

	template <typename T>
	bool operator<(const shared_ptr<T>& lhs, nullptr_t) noexcept
	{
		return std::less<T *>()(lhs.get(), nullptr);
	}

	template <typename T, typename U>
	bool operator>(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return std::less<void *>()(static_cast<void *>(rhs.get()), static_cast<void *>(lhs.get()));
	}

	template <typename T>
	bool operator>(nullptr_t, const shared_ptr<T>& rhs) noexcept
	{
		return std::greater<T *>()(nullptr, rhs.get());
	}

	template <typename T>
	bool operator>(const shared_ptr<T>& lhs, nullptr_t) noexcept
	{
		return std::greater<T *>()(lhs.get(), nullptr);
	}

	template <typename T, typename U>
	bool operator<=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return !(lhs>rhs);
	}

	template <typename T>
	bool operator<=(nullptr_t, const shared_ptr<T>& rhs) noexcept
	{
		return !(nullptr > rhs);
	}
	template <typename T>
	bool operator<=(const shared_ptr<T>& lhs, nullptr_t) noexcept
	{
		return !(lhs > nullptr);
	}

	template <typename T, typename U>
	bool operator>=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return !(lhs>rhs);
	}

	template <typename T>
	bool operator>=(nullptr_t, const shared_ptr<T>& rhs) noexcept
	{
		return !(nullptr < rhs);
	}

	template <typename T>
	bool operator>=(const shared_ptr<T>& lhs, nullptr_t) noexcept
	{
		return !(lhs < nullptr);
	}
} // namespace stepik

int main(){
  return 0;
}
