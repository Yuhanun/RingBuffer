#include <iostream>
#include <memory>
#include <numeric>

template <typename T, size_t buffer_size>
class RingBuffer {
public:
    RingBuffer() {
        _ptr = new T[buffer_size];
        _write_ptr = _ptr;
    }

    ~RingBuffer() {
        delete[] _ptr;
    }

    RingBuffer(RingBuffer&& buff) noexcept {
        _ptr = buff._ptr;
        buff._ptr = nullptr;
        _write_ptr = buff._write_ptr;
        buff._write_ptr = nullptr;
    }

    RingBuffer(RingBuffer const& buff) noexcept {
        if (!_ptr) {
            _ptr = new T[buffer_size];
        }
        _write_ptr = _ptr;
        for (auto& each : buff) 
            write(each);
    }

    RingBuffer& operator=(RingBuffer&&) = default;
    RingBuffer& operator=(RingBuffer const&) = default;

    T* begin() const noexcept {
        return _ptr;
    }

    T* end() const noexcept {
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
        static_assert(std::is_same<char, T>::value, "RingBuffer<T, buffer_size>::as_string() can only be called when T is char");
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