#pragma once

template<typename Container, typename Function>
void call_each(Container& container, Function f)
{
	for (auto& value : container) {
		(value.*f)();
	}
}

template<typename Container>
void call_each(Container& container)
{
	for (auto& value : container) {
		value();
	}
}