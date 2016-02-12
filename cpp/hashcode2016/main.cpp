#include <QCoreApplication>

#include "parser.h"
#include "warehousemanager.h"
#include "ordermanager.h"
#include "dronemanager.h"

void run_simu(WarehouseManager & wm, OrderManager & om, DroneManager & dm);

// -------------------------------------------------------------------------------
// main section
// -------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // -- parsing
    Parser p = Parser::parse(argv[1]);

    // -- init managers
    WarehouseManager wm;
    OrderManager om;
    DroneManager dm;

    // -- run simulation
    run_simu(wm, om, dm);

    return a.exec();
}

// -------------------------------------------------------------------------------
// simulation section
// -------------------------------------------------------------------------------

void update_drones(WarehouseManager & wm, OrderManager & om, DroneManager & dm);

void run_simu(WarehouseManager & wm, OrderManager & om, DroneManager & dm)
{
    // tant qu'on a pas atteint la fin de la simulation
    while(!dm.simu_finished())
    {   // on met a jour les drone en donnant des ordres si necessaire
        update_drones(wm, om, dm);
        // on fait avancer la simulation d'un pas
        dm.next_turn();
    }
}

void load_drone(Drone * drone, Order * order, WarehouseManager & wm);

void update_drones(WarehouseManager & wm, OrderManager & om, DroneManager & dm)
{   // tant qu'on a un drone disponible
    Drone * drone;
    while((drone = dm.next_available_drone()) != NULL)
    {   // si une commande non traitée subsiste
        Order * order = om.next_unhandled_order();
        if(order != NULL)
        {   // on charge le drone avec les items de la commande
            load_drone(drone, order, wm);
        }
        else // si aucune commande n'existe on break
        {   break;
        }
    }
}

void load_drone(Drone * drone, Order * order, WarehouseManager & wm)
{   // recuperation de l'item restant
    ItemLeft item_left;
    // tant que le drone n'est pas plein ou que la commande n'est pas complète
    while( (item_left = order->item_left()).valid && !drone->is_full(item_left))
    {   // si on a au moins une une warehouse qui possède l'item
        Warehouse * warehouse = wm.get_closest_having(item_left, drone);
        if(warehouse != NULL)
        {   // on demande au drone de charger
            drone->load(item_left, warehouse, order);
        }
        else // aucune warehouse ne contient cet item
        {   order->cancel(); // on abandonne la commande doit être abandonnée
            break;
        }
        // quand on arrive là, la commande est abandonnée OU la commande est chargée OU le drone est plein
        if(order->state() != Order::TERMINATED) {
            drone->deliver(order);
        }
    }
}


