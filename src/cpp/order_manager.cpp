#include "../hpp/order_manager.hpp"



/* class Order: */
/*------------------------------------------------------------------------------------------------------------------------*/
void ORDERMANAGER::Order::createOrder(const uint32_t& order_id)
{
	OrderItem item(order_id);

	this->current_orders.insert( std::make_pair(order_id, item) );
}
/*------------------------------------------------------------------------------------------------------------------------*/
ORDERMANAGER::OrderItem& ORDERMANAGER::Order::getItem(const uint32_t order_id)
{
   auto it = current_orders.find(order_id);
   if (it != current_orders.end())
      return it->second;
   else { std::cout << "Order item not found\n"; }
}
/*------------------------------------------------------------------------------------------------------------------------*/
/* static field: */
std::map <uint32_t, ORDERMANAGER::OrderItem> ORDERMANAGER::Order::current_orders;
/*------------------------------------------------------------------------------------------------------------------------*/



/* class Order Item: */
/*------------------------------------------------------------------------------------------------------------------------*/
void ORDERMANAGER::OrderItem::addMeal(const uint32_t& meal_id, const uint8_t& quantity)
{
   this->item.meal_quantity.insert( std::make_pair(meal_id, quantity) );
}
/*------------------------------------------------------------------------------------------------------------------------*/
void ORDERMANAGER::OrderItem::displayOrder()
{
   std::cout << "\n\n----------------------\n  Display order: #" << this->item.order_id << "\n----------------------\n";
   for (const auto &el : item.meal_quantity)
   {
      std::cout << "\n  Meal: " << el.first << "\n";
      std::cout << "  Quantity: " << static_cast<int>(el.second) << "\n\n";
   }

   std::cout << "----------------------\n\n\n";
}
/*------------------------------------------------------------------------------------------------------------------------*/