/*
#include<chrono>
class RateLimiter {
private:
    std::chrono::steady_clock::time_point last_call_time;
    std::chrono::milliseconds limit_duration;

public:
    RateLimiter(int milliseconds) : limit_duration(milliseconds) {
        // Initialize to a time far in the past so the first call always succeeds
        last_call_time = std::chrono::steady_clock::now() - limit_duration - std::chrono::seconds(1);
    }

    bool canRequest() {
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_call_time) >= limit_duration) {
            last_call_time = now;
            return true;
        }
        return false;
    }

    // Since we cannot block/sleep, this helper allows the caller to know how long to wait
    // if they decided to implement a wait loop elsewhere.
    long long getWaitTimeMs() {
        auto now = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_call_time);
        if (diff >= limit_duration) return 0;
        return (limit_duration - diff).count();
    }
};*/
