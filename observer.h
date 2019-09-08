#pragma once
#include <map>
#include <mutex>
#include <utility>
using namespace std;
template <typename Func>
class Event {
public:
	int AddObserver(Func f) {
		lock_guard<mutex> lock(mutex_);
		observer_map_.emplace(count, f);
		return count++;

	};
	int DeleteObserver(int id) {
		lock_guard<mutex> lock(mutex_);
		for (auto iter : observer_map_) {
			if (iter.first == id) {
				observer_map_.erase(id);
				return 0;
			}
		}

		return -1;

	};
template <typename ...Args>
	void Notify(Args... args) {
		lock_guard<mutex> lock(mutex_);
		for (auto iter : observer_map_) {
			Func f = iter.second;
			f(args...);
		}
	};

private:
	map<int, Func> observer_map_;
	mutex mutex_;
	int count{0};

};

//
//template <typename Func>
//int Event::AddObserver(Func f) {
//	lock_guard<mutex> lock(mutex_);
//	observer_map_.emplace(count, f);
//	return count++;
//
//}
//
//
//template <typename Func>
//int Event::DeleteObserver(int id) {
//	lock_guard<mutex> lock(mutex_);
//	for (auto iter : observer_map_) {
//		if (iter.first == id){
//			observer_map_.erase(id);
//			return 0;
//		}
//	}
//
//	return -1;
//
//}
//
//template <typename Func>
//template <typename... Args>
//void Event::Notify(Args... args) {
//	lock_guard<mutex> lock(mutex_);
//	for (auto iter::observer_map_) {
//		Func f = iter.second;
//		f(args...);
//	}
//}
