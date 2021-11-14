#ifndef STACK_HPP
# define STACK_HPP

# include "iterators_utils.hpp"
# include "vector.hpp"

namespace ft {

	template<
		class T,
		class Container = ft::vector<T>
	> class stack {
	public:
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

	private:
		container_type c;

	public:
		explicit stack( const Container& cont = Container() ) : c(cont) {}
		stack( const stack& other ) : c(other.c) {}
		~stack() {};
		stack & operator=(const stack & other) {
			this->c = other.c;
			return (*this);
		}

		reference top() { return (c.back()); }

		const_reference top() const { return (c.back()); }

		bool empty() const { return (c.empty()); }
		size_type size() const { return (c.size()); }

		void push( const value_type& value ) { c.push_back(value); }
		void pop() { c.pop_back(); }

		template< class type, class container >
		friend bool operator==( const ft::stack<type,container>& lhs, const ft::stack<type,container>& rhs );
		template< class type, class container >
		friend bool operator!=( const ft::stack<type,container>& lhs, const ft::stack<type,container>& rhs );
		template< class type, class container >
		friend bool operator<( const ft::stack<type,container>& lhs, const ft::stack<type,container>& rhs );
		template< class type, class container >
		friend bool operator<=( const ft::stack<type,container>& lhs, const ft::stack<type,container>& rhs );
		template< class type, class container >
		friend bool operator>( const ft::stack<type,container>& lhs, const ft::stack<type,container>& rhs );
		template< class type, class container >
		friend bool operator>=( const ft::stack<type,container>& lhs, const ft::stack<type,container>& rhs );

	};

	template< class type, class container >
	bool operator==( const ft::stack<type,container>& lhs, const ft::stack<type,container>& rhs ) { return (lhs.c == rhs.c); }
	template< class type, class container >
	bool operator!=( const ft::stack<type,container>& lhs, const ft::stack<type,container>& rhs ) { return (lhs.c != rhs.c); }
	template< class type, class container >
	bool operator<( const ft::stack<type,container>& lhs, const ft::stack<type,container>& rhs ) { return (lhs.c < rhs.c); }
	template< class type, class container >
	bool operator<=( const ft::stack<type,container>& lhs, const ft::stack<type,container>& rhs ) { return (lhs.c <= rhs.c); }
	template< class type, class container >
	bool operator>( const ft::stack<type,container>& lhs, const ft::stack<type,container>& rhs ) { return (lhs.c > rhs.c); }
	template< class type, class container >
	bool operator>=( const ft::stack<type,container>& lhs, const ft::stack<type,container>& rhs ) { return (lhs.c >= rhs.c); }
}

#endif