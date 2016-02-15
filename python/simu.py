from drone import DRONE_STATUS
#
#   DM = DroneManager
#   OM = OrderManager
#   WM = WarehouseManager
#
from order import ORDER_STATUS


def load_drone(drone, order, WM):
    item_id, item_qty = order.item_left() # recuperation de l'item restant
    # tant que le drone n'est pas plein ou que la commande n'est pas complète
    qty = drone.max_qty(item_id, item_qty)
    while item_id is not None and (qty > 0):
        # si on a au moins une une warehouse qui possède l'item

        warehouse = WM.get_closest_having(item_id, qty, drone)

        if warehouse is not None:
            # on demande au drone de charger

            drone.load(warehouse, item_id, qty, order)

        else: # aucune warehouse ne contient cet item 
            # on abandonne la commande doit être abandonnée

            order.cancel()
            drone.status = DRONE_STATUS.AVAILABLE

            break
        # on recupere le dernier item
        item_id, item_qty = order.item_left() # recuperation de l'item restant
        qty = drone.max_qty(item_id, item_qty)
        # quand on arrive là, la commande est abandonnée OU la commande est chargée OU le drone est plein
    # si le drone est plein OU la commande est complètement chargée
    if order.status != ORDER_STATUS.TERMINATED:
        # on dit au drone de faire la livraison
        drone.deliver_all(order) # , item_id, item_qty)


def update_drones(DM, OM, WM):
    # tant qu'on a un drone disponible
    drone = DM.next_available_drone()
    max_it = 100
    i = 0
    while drone is not None:
        # si une commande non traitée subsiste

        order = OM.next_unhandled_order()
        if not order is None:

            load_drone(drone, order, WM)

        else: # si aucune commande existe 
            # le drone attend
            break#drone.wait()
        # on va chercher le prochain drone disponible

        drone = DM.next_available_drone()

        i += 1


def simu(DM, OM, WM):
    # tant qu'on a pas atteint la fin de la simulation
    while not DM.simu_finished():
        # on met a jour les drone en donnant des ordres si necessaire
        update_drones(DM, OM, WM)
        # on fait avancer la simulation d'un pas

        DM.next_turn()
        
