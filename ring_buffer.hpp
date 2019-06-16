#include <iostream>
#include <memory>
#include <numeric>

template <typename T, size_t buffer_size>
class ring_buffer {
public:
    using iterator = T*;
    using const_iterator = const T*;

    ring_buffer() {
        _ptr = new T[buffer_size];
        _write_ptr = _ptr;
    }

    ~ring_buffer() {
        delete[] _ptr;
    }

    ring_buffer(ring_buffer&& buff) noexcept {
        _ptr = buff._ptr;
        buff._ptr = nullptr;
        _write_ptr = buff._write_ptr;
        buff._write_ptr = nullptr;
    }

    ring_buffer(ring_buffer const& buff) noexcept {
        if (!_ptr) {
            _ptr = new T[buffer_size];
        }
        _write_ptr = _ptr;
        for (auto& each : buff) 
            write(each);
    }

    ring_buffer& operator=(ring_buffer&&) = default;
    ring_buffer& operator=(ring_buffer const&) = default;

    iterator begin() const noexcept {
        return _ptr;
    }

    iterator end() const noexcept {
        return _ptr + buffer_size;
    }

    const_iterator begin() const noexcept {
        return _ptr;
    }

    const_iterator end() const noexcept {
        return _ptr + buffer_size;
    }

    T* write(T&& val) {
        set_write_ptr();
        *_write_ptr = std::forward<T>(val);
        return ++_write_ptr;
    }

    T* write(T const& val) {
        set_write_ptr();
        *_write_ptr = std::forward<T>(val);
        return ++_write_ptr;
    }

    size_t size() const {
        return buffer_size;
    }

    std::string as_string() const {
        static_assert(std::is_same<char, T>::value, "ring_buffer<T, buffer_size>::as_string() can only be called when T is char");
        return std::accumulate<char*, std::string>(begin(), end(), "");
    }

    explicit operator std::string() {
        return as_string();
    }

private:
    void set_write_ptr() {
        if (_write_ptr == end())
            _write_ptr = begin();
    }

    T* _ptr;
    T* _write_ptr;
};