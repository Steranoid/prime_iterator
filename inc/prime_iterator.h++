//prime_iterator is a header-only library design to iterate between prime numbers
//Copyright (C) 2017 Steranoid

//This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

//You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef PRIME_ITERATOR
#define PRIME_ITERATOR

#include <memory>
#include <vector>

namespace steranoid {
	template <typename T = unsigned long long>
	class prime_iterator {
	public:
		using size_type = unsigned long;
		using type = T;

		//Construct and assign
		prime_iterator(size_type n = type()) : _p(new primes_vector{2,3}), _i(type()) {
			i(n);
		}
		prime_iterator & operator=(size_type n) {
			auto copy = *this;
			copy.i(n);
			return operator=(copy);
		}

		//Copy
		prime_iterator(prime_iterator const &) = default;
		prime_iterator & operator=(prime_iterator const &) = default;

		//Move
		prime_iterator(prime_iterator &&) = default;
		prime_iterator & operator=(prime_iterator &&) = default;

		//arithmetic
		inline prime_iterator operator+(size_type n) const {
			return prime_iterator(*this) += n;
		}
		inline prime_iterator operator-(size_type n) const {
			return prime_iterator(*this) -= n;
		}

		//coumpound assignment
		inline prime_iterator & operator+=(size_type n) {
			return operator=(i() + n);
		}
		inline prime_iterator & operator-=(size_type n) {
			return operator=(i() - n);
		}
		inline prime_iterator & operator++() {
			return operator+=(1);
		}
		prime_iterator operator++(int) {
			auto copy = *this;
			operator++();
			return copy;
		}
		inline prime_iterator & operator--() {
			return operator-=(1);
		}
		prime_iterator operator--(int) {
			auto copy = *this;
			operator--();
			return copy;
		}

		inline type operator*() const {
			return (*_p)[i()];
		}

		static bool is_prime(type n, prime_iterator p = prime_iterator()) {
			auto i = p;
			i = 0ul;
			for (; (*i)*(*i) < n and n % (*i) != 0; ++i) {}
			return n % (*i) != 0;
		}

	private:
		using primes_vector = std::vector<type>;
		using pv_ptr = std::shared_ptr<primes_vector>;

		void calculate_next_prime() {
			auto prime = _p->back() + 2;
			for (;!is_prime(prime,*this); prime += 2) {}
			_p->push_back(prime);
		}

		void i(size_type n) {
			_i = n;
			for (;_p->size() <= i(); calculate_next_prime()) {}
		}
		inline size_type i() const {
			return _i;
		}

		pv_ptr _p;

		size_type _i;
	};
}

#endif
