#pragma once
#include <thread>
#include <utility>

//safe wrapper for std::thread - the thread, if joinable, joins in destructor; analog of std::jthread in c++20
class JoiningThread {
private:
	std::thread t;

public:
	JoiningThread() noexcept = default;
	
	template <typename Callable, typename... Args>
	explicit JoiningThread(Callable &&func, Args&&... args) : t(std::forward<Callable>(func), std::forward<Args>(args)...) {}

	explicit JoiningThread(std::thread t) noexcept : t(std::move(t)) {}

	JoiningThread(JoiningThread &&other) noexcept : t(std::move(other.t)) {}

	JoiningThread& operator=(JoiningThread&& other) noexcept {
		if (joinable()) join();
		t = std::move(other.t);
		return *this;
	}

	JoiningThread& operator=(std::thread other) noexcept {
		if (joinable()) join();
		t = std::move(other);
		return *this;
	}

	//in any case the thread will join while outside function exiting, avoiding std::terminate() call
	~JoiningThread() noexcept {
		if (joinable()) join();
	}

	std::thread::id getId() const noexcept {
		return t.get_id();
	}

	std::thread& getThread() noexcept {
		return t;
	}

	std::thread const& getThread() const noexcept {
		return t;
	}

	bool joinable() const noexcept {
		return t.joinable();
	}

	void join() {
		t.join();
	}

	void detach() {
		t.detach();
	}
};