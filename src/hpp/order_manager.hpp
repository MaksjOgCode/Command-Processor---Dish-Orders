#ifndef ORDERMANAGER_HPP
#define ORDERMANAGER_HPP



#include <string>
#include <map>
#include <iostream>
#include <expected>



namespace ORDERMANAGER
{

	/*------------------------------------------------------------------------------------------------------------------------*/
	class OrderItem
	{
	public:
		OrderItem(const uint32_t& _order_id)
		{
			this->item.order_id = _order_id;
		}

		void addMeal(const uint16_t &meal_id, const uint8_t &quantity);

		void displayOrder();

		bool isNoneItem() const noexcept;
	private:
		struct Item
		{
		public:
			/* The ID must be unique: */
			uint32_t order_id{};

			/* uint16_t = meal-id | uint8_t = quantity */
			std::map <uint32_t, uint8_t> meal_quantity {};
		};

		Item item {};
	};
	/*------------------------------------------------------------------------------------------------------------------------*/



	/*  */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class Order
	{
	public:
		void createOrder(const uint32_t &order_id);
		std::expected<ORDERMANAGER::OrderItem*, std::string> getItem(const uint32_t order_id);
	private:
		static std::map <uint32_t, OrderItem> current_orders;
	};
	/*------------------------------------------------------------------------------------------------------------------------*/

};
namespace OMNG = ORDERMANAGER;



#endif /* !ORDERMANAGER_HPP! */