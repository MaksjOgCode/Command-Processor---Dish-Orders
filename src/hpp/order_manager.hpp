#ifndef ORDERMANAGER_HPP
#define ORDERMANAGER_HPP



#include <string>
#include <map>
#include <iostream>



namespace ORDERMANAGER
{

	/*------------------------------------------------------------------------------------------------------------------------*/
	class OrderItem
	{
	public:
		OrderItem(const uint16_t& _order_id)
		{
			this->item.order_id = _order_id;
		}

		void addMeal(const uint16_t &meal_id, const uint8_t &quantity);

		void displayOrder();
	private:
		struct Item
		{
		public:
			/* The ID must be unique: */
			uint16_t order_id{};

			/* uint16_t = meal-id | uint8_t = quantity */
			std::map <uint16_t, uint8_t> meal_quantity {};
		};

		Item item {};
	};
	/*------------------------------------------------------------------------------------------------------------------------*/



	/*  */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class Order
	{
	public:
		void createOrder(const uint16_t &order_id);
		OrderItem& getItem(const uint16_t order_id);
	private:
		static std::map <uint16_t, OrderItem> current_orders;
	};
	/*------------------------------------------------------------------------------------------------------------------------*/

};
namespace OMNG = ORDERMANAGER;



#endif /* !ORDERMANAGER_HPP! */