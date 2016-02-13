#include "simulator.h"

#include "src/utils/macro.h"

void Simulator::run_simu(WarehouseManager & wm, OrderManager & om, DroneManager & dm)
{   // tracing -----------------------------------------------------------
    TRACE("Simulator","run_simu","simu beginning.");
    // tracing -----------------------------------------------------------
    // tant qu'on a pas atteint la fin de la simulation
    while(!dm.simu_finished())
    {   // on met a jour les drone en donnant des ordres si necessaire
        _update_drones(wm, om, dm);
        // on fait avancer la simulation d'un pas
        dm.next_turn();
        // tracing -----------------------------------------------------------
        TRACE("Simulator","run_simu","simu next turn.");
        // tracing -----------------------------------------------------------
    }
}

void Simulator::_update_drones(WarehouseManager & wm, OrderManager & om, DroneManager & dm)
{   // tant qu'on a un drone disponible
    Drone * drone;
    while((drone = dm.next_available_drone()) != NULL)
    {   // si une commande non traitée subsiste
        Order * order = om.next_unhandled_order();
        if(order != NULL)
        {   // on charge le drone avec les items de la commande
            _load_drone(drone, order, wm);
        }
        else // si aucune commande n'existe on break
        {   break;
        }
    }
}

void Simulator::_load_drone(Drone * drone, Order * order, WarehouseManager & wm)
{
    Item item;
    bool load;
    do
    {   // recuperation de l'item restant
        item = order->item_left();
        load = _update_load(item, drone);
        if(load)
        {   // si on a au moins une une warehouse qui possède l'item
            Warehouse * warehouse = wm.get_closest_having(item, drone);
            if(warehouse != NULL)
            {   // on demande au drone de charger
                drone->load(item, warehouse, order);
            }
            else // aucune warehouse ne contient cet item
            {   order->cancel(); // on abandonne la commande doit être abandonnée
                break;
            }
            // quand on arrive là, la commande est abandonnée OU la commande est chargée OU le drone est plein
            // si le statut de la commande est différent de TERMINATED (la commande est complètement livrée OU abandonnée)
            if(order->state() != Order::TERMINATED) {
                // on livre tous les items de la commande
                drone->deliver(order);
            }
        }
    } while(load);
}

bool Simulator::_update_load(const Item & item, Drone * drone)
{
    bool ok = true;
    if(!item.valid)
    {   TRACE("Simulator","_update_load","order fully loaded");
        ok = false;
    }
    else if(drone->is_full(item))
    {   TRACE("Simulator","_update_load","drone is full");
        ok = false;
    }
    return ok;
}
