#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>

struct Item {
	std::string name;
	std::string type;
	int value;
	double weight;

	std::string rarity;

	Item(const std::string& n, const std::string& t, int v, double w, const std::string& r)
		: name(n), type(t), value(v), weight(w), rarity(r) {}

	std::string toString() const {
		std::string displayName = name;
		if (rarity == "легендарный") {
			displayName = "[Легендарный " + name + "]";
		} else if (rarity == "эпический") {
			displayName = "[Эпический " + name + "]";
		} else if (rarity == "редкий") {
			displayName = "[Редкий " + name + "]";
		}
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(2) << weight;
		return displayName + " (тип: " + type + ", ценность: " + std::to_string(value) + ", вес: " + oss.str() + ", редкость: " + rarity + ")";
	}
};

struct Inventory {
	void findItemByName(const std::string& searchName) const {
		bool found = false;
		for (size_t i = 0; i < items.size(); ++i) {
			if (items[i].name == searchName) {
				std::cout << i + 1 << ". " << items[i].toString() << std::endl;
				found = true;
			}
		}
		if (!found) {
			std::cout << "Предмет с названием '" << searchName << "' не найден." << std::endl;
		}
	}
	void sortByValue() {
		std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
			return a.value > b.value;
		});
		std::cout << "Инвентарь отсортирован по ценности (по убыванию)." << std::endl;
	}

	void sortByName() {
		std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
			return a.name < b.name;
		});
		std::cout << "Инвентарь отсортирован по алфавиту." << std::endl;
	}
	int totalValue() const {
		int sum = 0;
		for (const auto& item : items) sum += item.value;
		return sum;
	}
	std::vector<Item> items;
	double maxWeight = 30.0; // лимит вместимости

	double currentWeight() const {
		double sum = 0.0;
		for (const auto& item : items) sum += item.weight;
		return sum;
	}

	void addItem(const Item& item) {
		if (currentWeight() + item.weight > maxWeight) {
			std::cout << "Инвентарь переполнен! Текущий вес: " << currentWeight() << ", лимит: " << maxWeight << std::endl;
			std::cout << "Удалить старый предмет (1) или отказаться от нового (2)? ";
			int action;
			std::cin >> action;
			std::cin.ignore();
			if (action == 1 && !items.empty()) {
				std::cout << "Введите номер предмета для удаления: ";
				int idx;
				std::cin >> idx;
				std::cin.ignore();
				removeItem(idx);
				addItem(item); // повторная попытка
			} else {
				std::cout << "Новый предмет не добавлен." << std::endl;
			}
			return;
		}
		items.push_back(item);
		std::cout << "Предмет добавлен!" << std::endl;
	}

	void showItems() const {
		if (items.empty()) {
			std::cout << "Инвентарь пуст." << std::endl;
			return;
		}
		std::cout << "Ваш инвентарь:" << std::endl;
		for (size_t i = 0; i < items.size(); ++i) {
			std::cout << i + 1 << ". " << items[i].toString() << std::endl;
		}
		std::cout << "Общая ценность инвентаря: " << totalValue() << std::endl;
	}

	void removeItem(int index) {
		if (items.empty()) {
			std::cout << "Инвентарь пуст. Нечего удалять." << std::endl;
			return;
		}
		if (index < 1 || index > (int)items.size()) {
			std::cout << "Неверный номер предмета." << std::endl;
			return;
		}
		items.erase(items.begin() + (index - 1));
		std::cout << "Предмет удалён." << std::endl;
	}
};

int main() {
	Inventory inventory;
	int choice = -1;
	while (choice != 0) {
		std::cout << "\nМеню:\n";
		std::cout << "1 - Добавить предмет\n";
		std::cout << "2 - Показать инвентарь\n";
		std::cout << "3 - Удалить предмет\n";
		std::cout << "4 - Сортировать инвентарь\n";
	std::cout << "5 - Поиск предмета по названию\n";
	std::cout << "0 - Выйти\n";
		std::cout << "Ваш выбор: ";
		std::cin >> choice;
		std::cin.ignore();
		switch (choice) {
			case 1: {
				std::string name, type, rarity;
				int value;
				double weight;
				std::cout << "Введите название предмета: ";
				std::getline(std::cin, name);
				std::cout << "Введите тип предмета (оружие/зелье/броня/что-нибудь еще): ";
				std::getline(std::cin, type);
				std::cout << "Введите ценность предмета: ";
				std::cin >> value;
				std::cin.ignore();
				std::cout << "Введите вес предмета: ";
				std::cin >> weight;
				std::cin.ignore();
				std::cout << "Введите редкость предмета (обычный/редкий/эпический/легендарный): ";
				std::getline(std::cin, rarity);
				inventory.addItem(Item(name, type, value, weight, rarity));
				break;
			}
			case 2:
				inventory.showItems();
				break;
			case 3: {
				int idx;
				std::cout << "Введите номер предмета для удаления: ";
				std::cin >> idx;
				std::cin.ignore();
				inventory.removeItem(idx);
				break;
			}
			case 4: {
				std::cout << "Сортировать по: 1 - ценности, 2 - алфавиту: ";
				int sortChoice;
				std::cin >> sortChoice;
				std::cin.ignore();
				if (sortChoice == 1) {
					inventory.sortByValue();
				} else if (sortChoice == 2) {
					inventory.sortByName();
				} else {
					std::cout << "Неверный выбор сортировки." << std::endl;
				}
				break;
			}
			case 5: {
				std::string searchName;
				std::cout << "Введите название предмета для поиска: ";
				std::getline(std::cin, searchName);
				inventory.findItemByName(searchName);
				break;
			}
			case 0:
				std::cout << "Выход..." << std::endl;
				break;
			default:
				std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
		}
	}
	return 0;
}
