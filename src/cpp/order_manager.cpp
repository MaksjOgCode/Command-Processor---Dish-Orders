#include "../hpp/order_manager.hpp"



/*------------------------------------------------------------------------------------------------------------------------*/
void ORDERMANAGER::Order::createOrder(const uint16_t& order_id)
{
	OrderItem item(order_id);

	this->current_orders.insert( std::make_pair(order_id, item) );
}
/*------------------------------------------------------------------------------------------------------------------------*/
ORDERMANAGER::OrderItem& ORDERMANAGER::Order::getItem(const uint16_t order_id)
{
   auto it = current_orders.find(order_id);
   if (it != current_orders.end()) {
      return it->second;
   } else {
      std::cout << "Order item not found\n";
   }
}
/*------------------------------------------------------------------------------------------------------------------------*/
std::map <uint16_t, ORDERMANAGER::OrderItem> ORDERMANAGER::Order::current_orders;




void ORDERMANAGER::OrderItem::addMeal(const uint16_t& meal_id, const uint8_t& quantity)
{
   this->item.meal_quantity.insert( std::make_pair(meal_id, quantity) );
}

void ORDERMANAGER::OrderItem::displayOrder()
{
   std::cout << "==========\n";
   for (const auto &el : item.meal_quantity)
   {
      std::cout << "Meal: " << el.first << "\n";
      std::cout << "Quantity: " << static_cast<int>(el.second) << "\n";
      std::cout << "==========\n";
   }
}