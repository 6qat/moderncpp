// open closed principle
// open for extension, closed for modification

#include <string>
#include <vector>
#include <iostream>

using namespace std;

enum class Color {
	red, green, blue
};

enum class Size {
	small, medium, large
};

struct Product {
	string name;
	Color color;
	Size size;
};

using Items = vector<Product*>;

struct ProductFilter {
//	typedef vector<Product*> Items;


	[[maybe_unused]] static Items by_color(const Items& items, const Color color)
	{
		Items result;
		for (auto& i : items)
			if (i->color==color)
				result.push_back(i);
		return result;
	}

	[[maybe_unused]] static Items by_size(const Items& items, const Size size)
	{
		Items result;
		for (auto& i : items)
			if (i->size==size)
				result.push_back(i);
		return result;
	}

	[[maybe_unused]] static Items by_size_and_color(const Items& items, const Size size, const Color color)
	{
		Items result;
		for (auto& i : items)
			if (i->size==size && i->color==color)
				result.push_back(i);
		return result;
	}
};

template<typename T>
struct Specification {
	virtual ~Specification() = default;

	virtual bool is_satisfied(T* item) const = 0;

	// new: breaks OCP if you add it post-hoc
	/*AndSpecification<T> operator&&(Specification<T>&& other)
	{
	  return AndSpecification<T>(*this, other);
	}*/
};

// Forward declaration
template<typename T>
struct AndSpecification;

// new:
template<typename T>
AndSpecification<T> operator&&(const Specification<T>& first, const Specification<T>& second)
{
	return { first, second };
}

template<typename T>
struct Filter {
	virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product> {
	Items filter(Items items, Specification<Product>& spec) override
	{
		Items result;
		for (auto& p : items)
			if (spec.is_satisfied(p))
				result.push_back(p);
		return result;
	}
};

struct ColorSpecification : Specification<Product> {
	Color color;

	explicit ColorSpecification(Color color)
			:color(color)
	{
	}

	bool is_satisfied(Product* item) const override
	{
		return item->color==color;
	}
};

struct SizeSpecification : Specification<Product> {
	Size size;

	explicit SizeSpecification(const Size size)
			:size{ size }
	{
	}

	bool is_satisfied(Product* item) const override
	{
		return item->size==size;
	}
};

template<typename T>
struct GeneralSpecification : Specification<Product> {
	T value;
	explicit GeneralSpecification(T value)
			:value(value) { }
	bool is_satisfied(T* item) const override
	{
		return false;
	}
};

template<typename T>
struct AndSpecification : Specification<T> {
	const Specification<T>& first;
	const Specification<T>& second;

	AndSpecification(const Specification<T>& first, const Specification<T>& second)
			:first(first), second(second)
	{
	}

	bool is_satisfied(T* item) const override
	{
		return first.is_satisfied(item) && second.is_satisfied(item);
	}
};

// new:

int main()
{
	auto apple = Product{ "Apple", Color::green, Size::small };
	auto tree = Product{ "Tree", Color::green, Size::large };
	auto house = Product{ "House", Color::blue, Size::large };

	const auto all = Items{ &apple, &tree, &house };

	auto bf = BetterFilter{};
	auto green = ColorSpecification{ Color::green };
	auto green_things = bf.filter(all, green);

	for (auto& x : green_things)
		cout << x->name << " is green\n";

	auto large = SizeSpecification{ Size::large };
	auto green_and_large = AndSpecification<Product>{ green, large };

	//auto big_green_things = bf.filter(all, green_and_large);

	// use the operator instead (same for || etc.)
	auto spec = green && large;
	for (auto& x : bf.filter(all, spec))
		cout << x->name << " is green and large\n";

	// warning: the following will compile but will NOT work
	// auto spec2 = SizeSpecification{Size::large} &&
	//              ColorSpecification{Color::blue};

//	getchar();
	return 0;
}