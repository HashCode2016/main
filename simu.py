
#
#   DM = DroneManager
#   OM = OrderManager
#   WM = WarehouseManager
#


def load_drone(drone, order, WM):
    item_id, item_qty = order.item_left() # recuperation de l'item restant
    # tant que le drone n'est pas plein ou que la commande n'est pas complète
    while not drone.is_full(item_id, item_qty) or not item_id is None: 
        # si on a au moins une une warehouse qui possède l'item
        warehouse = WM.get_closest_having(item_id, item_qty, drone)
        if warehouse is not None:
            # on demande au drone de charger
            drone.load(warehouse, item_id, item_qty, order)
        else: # aucune warehouse ne contient cet item 
            # on abandonne la commande doit être abandonnée
            order.cancel()
        # on recupere le dernier item
        item_id, item_qty = order.item_left() # recuperation de l'item restant
        # quand on arrive là, la commande est abandonnée OU la commande est chargée OU le drone est plein
    # si le drone est plein OU la commande est complètement chargée
    if drone.is_full(item_id, item_qty) or item_id is None:
        # on dit au drone de faire la livraison
        drone.deliver(order)


def update_drones(DM, OM, WM):
    # tant qu'on a un drone disponible
    drone = DM.next_available_drone()
    while not drone is None: 
        # si une commande non traitée subsiste
        order = OM.next_unhandled_order()
        if not order is None: 
            load_drone(drone, order, WM)
        else: # si aucune commande existe 
            # le drone attend
            drone.wait()
        # on va chercher le prochain drone disponible
        drone = DM.next_available_drone()


def simu(DM, OM, WM):
    # tant qu'on a pas atteint la fin de la simulation
    while not DM.simu_finished():
        print("A")
        # on met a jour les drone en donnant des ordres si necessaire
        update_drones(DM, OM, WM)
        print("B")
        # on fait avancer la simulation d'un pas
        DM.next_turn()
        
