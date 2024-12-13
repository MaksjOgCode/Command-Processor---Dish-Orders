#include "../hpp/order_manager.hpp"
#include "../hpp/menu_manager.hpp"


/* class Order: */
/*------------------------------------------------------------------------------------------------------------------------*/
void ORDERMANAGER::Order::createOrder(const uint32_t& order_id)
{
	OrderItem item(order_id);

	this->current_orders.insert( std::make_pair(order_id, item) );
}
/*------------------------------------------------------------------------------------------------------------------------*/
static ORDERMANAGER::OrderItem none_item(-1);
/*------------------------------------------------------------------------------------------------------------------------*/
std::expected<ORDERMANAGER::OrderItem*, std::string> ORDERMANAGER::Order::getItem(const uint32_t order_id)
{
   auto it = current_orders.find(order_id);
   if (it != current_orders.end())
      return std::expected<ORDERMANAGER::OrderItem*, std::string>(&it->second);
   else
      return std::unexpected("Order item not found:\n");
}
/*------------------------------------------------------------------------------------------------------------------------*/
/* static field: */
std::map <uint32_t, ORDERMANAGER::OrderItem> ORDERMANAGER::Order::current_orders;
/*------------------------------------------------------------------------------------------------------------------------*/



/* class Order Item: */
/*------------------------------------------------------------------------------------------------------------------------*/
void ORDERMANAGER::OrderItem::addMeal(const uint16_t& meal_id, const uint8_t& quantity)
{
   if ( this->item.meal_quantity.size() < 100 )
   {
      if (std::find(MENUMANAGER::Menu::available_id_meals.begin(), MENUMANAGER::Menu::available_id_meals.end(), meal_id) != MENUMANAGER::Menu::available_id_meals.end())
         this->item.meal_quantity.insert( std::make_pair(meal_id, quantity) );
      else
         std::cout << "There is no dish with such an ID\n";

   }
   else
      std::cout << "The order size cannot contain more 100 orders!\n";
   
   return;
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
bool ORDERMANAGER::OrderItem::isNoneItem() const noexcept
{
   return (this->item.order_id == -1);
}
/*------------------------------------------------------------------------------------------------------------------------*/