template <class T>
class SlideWindowMax {
public:
    SlideWindowMax(int window_size) :
        _window_size(window_size),
        _index(0) {}

    T addValue(T val) {
        while (!_dq.empty() && _index - _dq.front().second >= _window_size) {
            _dq.pop_front();
        }
        while (!_dq.empty() && _dq.back().first <= val) {
            _dq.pop_back();
        }
        _dq.emplace_back(val, _index++);
        return _dq.front().first;
    }

private:
    int _window_size;
    int _index;
    deque<pair<T, int>> _dq;
};
