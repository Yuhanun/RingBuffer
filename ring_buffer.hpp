#include <iostream>
#include <memory>
#include <numeric>

template <typename T, size_t buffer_size>
class ring_buffer {
public:
    using iterator = T*;
    using const_iterator = const T*;

    ring_buffer() noexcept
        : _ptr{ new T[buffer_size] }, _write_ptr{ _ptr.get() } 
    {}

    ring_buffer(ring_buffer&& other) noexcept
        : _ptr{ std::move(other._ptr) }, _write_ptr{ other._write_ptr } {
        other._write_ptr = nullptr;
    };

    ring_buffer& operator=(ring_buffer&& other) {
        if (this == &other) {
            return *this;
        }
        _ptr = std::move(other._ptr);
        _write_ptr = other._write_ptr;
        other._write_ptr = _write_ptr;
        return *this;
    };

    ring_buffer(ring_buffer const& buff) noexcept 
        : _ptr{ new T[buffer_size] }{
        for (auto const& each : buff) 
            write(each);
        _write_ptr = buff._write_ptr;
    }

    ring_buffer& operator=(ring_buffer const& buff) noexcept {
        if (this == &buff) {
            return *this;
        }
        _ptr = new T[buffer_size];
        for (auto const& each : buff) 
            write(each);
        _write_ptr = buff._write_ptr;
        return *this;
    };

    iterator begin() noexcept {
        return _ptr.get();
    }

    iterator end() noexcept {
        return begin() + buffer_size;
    }

    const_iterator cbegin() const noexcept {
        return _ptr.get();
    }

    const_iterator cend() const noexcept {
        return begin() + buffer_size;
    }

    T* write(T&& val) noexcept {
        set_write_ptr();
        *_write_ptr = std::forward<T>(val);
        return ++_write_ptr;
    }

    T* write(T const& val) noexcept {
        set_write_ptr();
        *_write_ptr = std::forward<T>(val);
        return ++_write_ptr;
    }

    size_t size() const noexcept {
        return buffer_size;
    }

    std::string as_string() const noexcept {
        static_assert(std::is_same<char, T>::value, "ring_buffer<T, buffer_size>::as_string() can only be called when T is char");
        return std::accumulate<char*, std::string>(begin(), end(), "");
    }

    explicit operator std::string() const noexcept {
        return as_string();
    }

private:
    void set_write_ptr() noexcept {
        if (_write_ptr == end())
            _write_ptr = begin();
    }

    std::unique_ptr<T[]> _ptr;
    T* _write_ptr;
};
