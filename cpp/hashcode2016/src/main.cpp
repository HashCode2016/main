#include <QCoreApplication>

#include "simulator.h"
#include "src/utils/parser.h"
#include "src/utils/writer.h"
#include "src/utils/macro.h"
#include "src/managers/warehousemanager.h"
#include "src/managers/ordermanager.h"
#include "src/managers/dronemanager.h"

// -------------------------------------------------------------------------------
// main section
// -------------------------------------------------------------------------------

void init_model_static(Parser & p);
void init_warehouse_manager(Parser & p, WarehouseManager & wm);
void init_order_manager(Parser & p, WarehouseManager & wm, OrderManager & om);
#ifdef ENABLE_DEBUG
void debug(WarehouseManager & wm, OrderManager & om, DroneManager & dm);
#endif

enum RETURN_CODES {
    ALL_GOOD = 0x00,
    MISSING_ARG = 0x01,
    PARSING_FAILED = 0x02,
    INIT_FAILED = 0x03
};

int main(int argc, char *argv[])
{
    if(argc < 3)
    {   ABORT("Main","main","missing at least one argument.\nMain: usage : ./hashcode2016 <input_file> <output_file> &> log.txt",MISSING_ARG);
    }
    // -- parsing
    Parser p = Parser::parse(argv[1]);
    if(!p.is_valid())
    {   ABORT("Main","main","parsing failed.",PARSING_FAILED);
    }
    INFO("Main","main","parsing done. Initializing model...");

    /// \warning DO NOT change initialization order
    // -- init classes statics
    init_model_static(p);

    // -- init warehouse manager
    WarehouseManager wm;
    init_warehouse_manager(p, wm);


    // -- init order manager
    OrderManager om;
    init_order_manager(p, wm, om);

    // -- init drone manager
    DroneManager dm(wm);
    // ---

#ifdef ENABLE_DEBUG
    debug(wm, om, dm);
#endif

    INFO("Main","main","model init done. Running simulation...");
    // -- run simulation
    Simulator::run_simu(wm, om, dm);
    INFO("Main","main","simulation done. Writing output...");

    Writer::write(argv[2], dm);

    INFO("Main","main","output writen. End.");

    exit(ALL_GOOD);
}

// -------------------------------------------------------------------------------
// debug section
// -------------------------------------------------------------------------------

#ifdef ENABLE_DEBUG
void debug(WarehouseManager & wm, OrderManager & om, DroneManager & dm)
{
    DEBUG("Main","debug","parsing result : width=" << Warehouse::MAP_SIZE().width());
    DEBUG("Main","debug","parsing result : height=" << Warehouse::MAP_SIZE().height());
    DEBUG("Main","debug","parsing result : drones=" << DroneManager::DRONE_COUNT());
    DEBUG("Main","debug","parsing result : turns=" << Drone::MAX_TURN());
    DEBUG("Main","debug","parsing result : max_weight=" << Drone::MAX_WEIGHT());
    DEBUG("Main","debug","parsing result : product_count=" << Warehouse::PRODUCT_COUNT());
    for(int i = 0; i < Warehouse::PRODUCT_COUNT(); ++i)
    {   DEBUG("Main","debug","parsing result : product_weight(id=" << i << ")=" << Warehouse::PRODUCTS_WEIGHT(i));
    }
    DEBUG("Main","debug","parsing result : WarehouseManager count=" << wm.count());
    DEBUG("Main","debug","parsing result : warehouses :" << wm.to_string().toStdString());
    DEBUG("Main","debug","parsing result : OrderManager count=" << om.count());
    DEBUG("Main","debug","parsing result : orders :" << om.to_string().toStdString());
    DEBUG("Main","debug","parsing result : DroneManager count=" << dm.count());
    DEBUG("Main","debug","parsing result : drones :" << dm.to_string().toStdString());
}
#endif
// -------------------------------------------------------------------------------
// model init section
// -------------------------------------------------------------------------------

#define PRELUDE_LEN 4
#define LINES_PER_WAREHOUSE 2
#define LINES_PER_ORDER 3

void init_model_static(Parser & p)
{
    INFO("Main","init_model_static","init model static.");
    QVector<int> v = p.get_int_line(0);
    if(v.count() != 5)
    {   ABORT("Main","init_model_static","init failed, incorrect mal formatted input line.",INIT_FAILED);
    }
    Warehouse::MAP_SIZE(QSize(v[1],v[0]));
    DroneManager::DRONE_COUNT(v[2]);
    Drone::MAX_TURN(v[3]);
    Drone::MAX_WEIGHT(v[4]);
    v = p.get_int_line(1);
    if(v.count() != 1)
    {   ABORT("Main","init_model_static","init failed, incorrect mal formatted input line.",INIT_FAILED);
    }
    Warehouse::PRODUCT_COUNT(v[0]);
    v = p.get_int_line(2);
    if(v.count() != Warehouse::PRODUCT_COUNT())
    {   ABORT("Main","init_model_static","init failed, incorrect mal formatted input line.",INIT_FAILED);
    }
    Warehouse::PRODUCTS_WEIGHT(0, v);
}

void init_warehouse_manager(Parser & p, WarehouseManager & wm)
{
    INFO("Main","init_warehouse_manager","init warehouse manager.");
    int warehouse_section_index = PRELUDE_LEN-1;
    QVector<int> v = p.get_int_line(warehouse_section_index);
    if(v.count() != 1)
    {   ABORT("Main","init_warehouse_manager","init failed, incorrect mal formatted input line.",INIT_FAILED);
    }
    for(int i = 0; i < v[0]; ++i)
    {   QVector<int> pos = p.get_int_line(warehouse_section_index + i * LINES_PER_WAREHOUSE + 1);
        QVector<int> items = p.get_int_line(warehouse_section_index + i * LINES_PER_WAREHOUSE + 2);
        if(pos.count() != 2 || items.count() != Warehouse::PRODUCT_COUNT())
        {   ABORT("Main","init_warehouse_manager","init failed, incorrect mal formatted input line.",INIT_FAILED);
        }
        // add a warehouse
        wm.add(i, QPoint(pos[1], pos[0]), items);
    }
}

void init_order_manager(Parser & p, WarehouseManager & wm, OrderManager & om)
{
    INFO("Main","init_order_manager","init order manager.");
    int order_section_index = PRELUDE_LEN + wm.count() * LINES_PER_WAREHOUSE;
    QVector<int> v = p.get_int_line(order_section_index);
    if(v.count() != 1)
    {   ABORT("Main","init_order_manager","init failed, incorrect mal formatted input line.",INIT_FAILED);
    }
    for(int i = 0; i < v[0]; ++i)
    {   QVector<int> pos = p.get_int_line(order_section_index + i * LINES_PER_ORDER + 1);
        QVector<int> item_count = p.get_int_line(order_section_index + i * LINES_PER_ORDER + 2);
        QVector<int> items = p.get_int_line(order_section_index + i * LINES_PER_ORDER + 3);
        if(pos.count() != 2 || item_count.count() != 1 || items.count() != item_count[0] )
        {   ABORT("Main","init_order_manager","init failed, incorrect mal formatted input line.",INIT_FAILED);
        }
        // convert input format to a more convenient format
        QVector<int> items_required(Warehouse::PRODUCT_COUNT(),0);
        for(int j=0; j < Warehouse::PRODUCT_COUNT(); ++j)
        {   items_required[j] = items.count(j);
        }
        // add a warehouse
        om.add(i, QPoint(pos[1], pos[0]), item_count[0], items_required);
    }
    // sort orders
    om.sort();
}
