#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "dependencies/AnsiiCodes.h"
#include "dependencies/Map.h"
#include "dependencies/List.h"
#include "dependencies/ScreenWriter.h"


/*

valgrind --leak-check=full --show-leak-kinds=all ./ti

leaks -atExit -- ./ti test/wizards.jpg


*/

typedef struct {
    char* unit_symbol;
    Map* converstions;
} Unit;

void define_length_units(List* units) {


    // m
    Map* m_map = new_map();
    double m_to_nm = 1000000000;
    m_put(m_map, "nm", &m_to_nm);
    double m_to_mm = 1000;
    m_put(m_map, "mm", &m_to_mm);
    double m_to_cm = 100;
    m_put(m_map, "cm", &m_to_cm);
    double m_to_m = 1;
    m_put(m_map, "m", &m_to_m);
    double m_to_km = 0.001;
    m_put(m_map, "km", &m_to_km);
    double m_to_in = 1 / 0.0254;
    m_put(m_map, "in", &m_to_in);
    double m_to_ft = 1 / 0.3048;
    m_put(m_map, "ft", &m_to_ft);
    double m_to_mile = 1 / 1609.344;
    m_put(m_map, "mile", &m_to_mile);
    Unit m = {
        "m",
        m_map
    };
    l_push(units, &m);

    // // nm
    // Map* nm_map = new_map();
    // double nm_to_mm = 0.000001;
    // m_put(nm_map, "mm", &nm_to_mm);
    // double nm_to_cm = 0.0000001;
    // m_put(nm_map, "cm", &nm_to_cm);
    // double nm_to_m = 0.000000001;
    // m_put(nm_map, "m", &nm_to_m);
    // double nm_to_km = 0.000000000001;
    // m_put(nm_map, "km", &nm_to_km);
    // double nm_to_in = 0.0000000393701;
    // m_put(nm_map, "in", &nm_to_in);
    // double nm_to_ft = 0.00000000328084;
    // m_put(nm_map, "ft", &nm_to_ft);
    // double nm_to_mile = 0.000000000000621371;
    // m_put(nm_map, "mile", &nm_to_mile);
    // Unit nm = {
    //     "nm",
    //     nm_map
    // };
    // l_push(units, &nm);

    // // mm
    // Map* mm_map = new_map();
    // double mm_to_nm = 1000000;
    // m_put(mm_map, "nm", &mm_to_nm);
    // double mm_to_cm = 0.1;
    // m_put(mm_map, "cm", &mm_to_cm);
    // double mm_to_m = 0.001;
    // m_put(mm_map, "m", &mm_to_m);
    // double mm_to_km = 0.000001;
    // m_put(mm_map, "km", &mm_to_km);
    // double mm_to_in = 0.0393701;
    // m_put(mm_map, "in", &mm_to_in);
    // double mm_to_ft = 0.00328084;
    // m_put(mm_map, "ft", &mm_to_ft);
    // double mm_to_mile = 0.0000000621371;
    // m_put(mm_map, "mile", &mm_to_mile);
    // Unit mm = {
    //     "mm",
    //     mm_map
    // };
    // l_push(units, &mm);

    // // cm
    // Map* cm_map = new_map();
    // double cm_to_nm = 10000000;
    // m_put(cm_map, "nm", &cm_to_nm);
    // double cm_to_mm = 10;
    // m_put(cm_map, "mm", &cm_to_mm);
    // double cm_to_m = 0.01;
    // m_put(cm_map, "m", &cm_to_m);
    // double cm_to_km = 0.00001;
    // m_put(cm_map, "km", &cm_to_km);
    // double cm_to_in = 0.393701;
    // m_put(cm_map, "in", &cm_to_in);
    // double cm_to_ft = 0.0328084;
    // m_put(cm_map, "ft", &cm_to_ft);
    // double cm_to_mile = 0.000000621371;
    // m_put(cm_map, "mile", &cm_to_mile);
    // Unit cm = {
    //     "cm",
    //     cm_map
    // };
    // l_push(units, &cm);


    // // km
    // Map* km_map = new_map();
    // double km_to_nm = 1000000000000;
    // m_put(km_map, "nm", &km_to_nm);
    // double km_to_mm = 1000000;
    // m_put(km_map, "mm", &km_to_mm);
    // double km_to_cm = 100000;
    // m_put(km_map, "cm", &km_to_cm);
    // double km_to_m = 1000;
    // m_put(km_map, "m", &km_to_m);
    // double km_to_in = 39370.1;
    // m_put(km_map, "in", &km_to_in);
    // double km_to_ft = 3280.84;
    // m_put(km_map, "ft", &km_to_ft);
    // double km_to_mile = 0.621371;
    // m_put(km_map, "mile", &km_to_mile);
    // Unit km = {
    //     "km",
    //     km_map
    // };
    // l_push(units, &km);

    // // km
    // Map* km_map = new_map();
    // double km_to_nm = 1000000000000;
    // m_put(km_map, "nm", &km_to_nm);
    // double km_to_mm = 1000000;
    // m_put(km_map, "mm", &km_to_mm);
    // double km_to_cm = 100000;
    // m_put(km_map, "cm", &km_to_cm);
    // double km_to_m = 1000;
    // m_put(km_map, "m", &km_to_m);
    // double km_to_in = 39370.1;
    // m_put(km_map, "in", &km_to_in);
    // double km_to_ft = 3280.84;
    // m_put(km_map, "ft", &km_to_ft);
    // double km_to_mile = 0.621371;
    // m_put(km_map, "mile", &km_to_mile);
    // Unit km = {
    //     "km",
    //     km_map
    // };
    // l_push(units, &km);

    // // in
    // Map* in_map = new_map();
    // double in_to_nm = 25400000;
    // m_put(in_map, "nm", &in_to_nm);
    // double in_to_mm = 25.4;
    // m_put(in_map, "mm", &in_to_mm);
    // double in_to_cm = 2.54;
    // m_put(in_map, "cm", &in_to_cm);
    // double in_to_m = 0.0254;
    // m_put(in_map, "m", &in_to_m);
    // double in_to_km = 0.0000254;
    // m_put(in_map, "km", &in_to_km);
    // double in_to_ft = 0.0833333;
    // m_put(in_map, "ft", &in_to_ft);
    // double in_to_mile = 0.000015783;
    // m_put(in_map, "mile", &in_to_mile);
    // Unit in = {
    //     "in",
    //     in_map
    // };
    // l_push(units, &in);

    // // ft
    // Map* ft_map = new_map();
    // double ft_to_nm = 304803316.224;
    // m_put(ft_map, "nm", &ft_to_nm);
    // double ft_to_mm = 304.8;
    // m_put(ft_map, "mm", &ft_to_mm);
    // double ft_to_cm = 30.48;
    // m_put(ft_map, "cm", &ft_to_cm);
    // double ft_to_m = 0.3048;
    // m_put(ft_map, "m", &ft_to_m);
    // double ft_to_km = 0.0003048;
    // m_put(ft_map, "km", &ft_to_km);
    // double ft_to_in = 12;
    // m_put(ft_map, "in", &ft_to_in);
    // double ft_to_mile = 0.000189394;
    // m_put(ft_map, "mile", &ft_to_mile);
    // Unit ft = {
    //     "ft",
    //     ft_map
    // };
    // l_push(units, &ft);

    // // mile
    // Map* mile_map = new_map();
    // double mile_to_nm = 304803316.224;
    // m_put(mile_map, "nm", &mile_to_nm);
    // double mile_to_mm = 304.8;
    // m_put(mile_map, "mm", &mile_to_mm);
    // double mile_to_cm = 30.48;
    // m_put(mile_map, "cm", &mile_to_cm);
    // double mile_to_m = 0.3048;
    // m_put(mile_map, "m", &mile_to_m);
    // double mile_to_km = 0.0003048;
    // m_put(mile_map, "km", &mile_to_km);
    // double mile_to_in = 12;
    // m_put(mile_map, "in", &mile_to_in);
    // double mile_to_mile = 0.000189394;
    // m_put(mile_map, "mile", &mile_to_mile);
    // Unit mile = {
    //     "mile",
    //     mile_map
    // };
    // l_push(units, &mile);
}

void define_mass_units(List* units) {


    // g
    Map* g_map = new_map();
    double g_to_g = 1;
    m_put(g_map, "g", &g_to_g);
    double g_to_mg = 1000;
    m_put(g_map, "mg", &g_to_mg);
    double g_to_kg = 0.001;
    m_put(g_map, "kg", &g_to_kg);
    double g_to_metric_ton = 0.000001;
    m_put(g_map, "metric_ton", &g_to_metric_ton);
    double g_to_oz = 16 / 453.59237;
    m_put(g_map, "oz", &g_to_oz);
    double g_to_lb = 1 / 453.59237;
    m_put(g_map, "lb", &g_to_lb);
    double g_to_us_ton = 1 / (2000 * 453.59237);
    m_put(g_map, "us_ton", &g_to_us_ton);
    Unit g = {
        "g",
        g_map
    };
    l_push(units, &g);

    // // mg
    // Map* mg_map = new_map();
    // double mg_to_g = 0.001;
    // m_put(mg_map, "g", &mg_to_g);
    // double mg_to_kg = 0.000001;
    // m_put(mg_map, "kg", &mg_to_kg);
    // double mg_to_metric_ton = 0.000000001;
    // m_put(mg_map, "metric_ton", &mg_to_metric_ton);
    // double mg_to_oz = 0.000035274;
    // m_put(mg_map, "oz", &mg_to_oz);
    // double mg_to_lb = 0.0000022046;
    // m_put(mg_map, "lb", &mg_to_lb);
    // double mg_to_us_ton = 0.0000000011023;
    // m_put(mg_map, "us_ton", &mg_to_us_ton);
    // Unit mg = {
    //     "mg",
    //     mg_map
    // };
    // l_push(units, &mg);

    // // g
    // Map* g_map = new_map();
    // double g_to_mg = 1000;
    // m_put(g_map, "mg", &g_to_mg);
    // double g_to_kg = 0.001;
    // m_put(g_map, "kg", &g_to_kg);
    // double g_to_metric_ton = 0.000001;
    // m_put(g_map, "metric_ton", &g_to_metric_ton);
    // double g_to_oz = 0.035274;
    // m_put(g_map, "oz", &g_to_oz);
    // double g_to_lb = 0.00220462;
    // m_put(g_map, "lb", &g_to_lb);
    // double g_to_us_ton = 0.0000011023;
    // m_put(g_map, "us_ton", &g_to_us_ton);
    // Unit g = {
    //     "g",
    //     g_map
    // };
    // l_push(units, &g);

    // // kg
    // Map* kg_map = new_map();
    // double kg_to_mg = 1000000;
    // m_put(kg_map, "mg", &kg_to_mg);
    // double kg_to_g = 1000;
    // m_put(kg_map, "g", &kg_to_g);
    // double kg_to_metric_ton = 0.001;
    // m_put(kg_map, "metric_ton", &kg_to_metric_ton);
    // double kg_to_oz = 35.274;
    // m_put(kg_map, "oz", &kg_to_oz);
    // double kg_to_lb = 2.20462;
    // m_put(kg_map, "lb", &kg_to_lb);
    // double kg_to_us_ton = 0.00110231;
    // m_put(kg_map, "us_ton", &kg_to_us_ton);
    // Unit kg = {
    //     "kg",
    //     kg_map
    // };
    // l_push(units, &kg);

    // // metric_ton
    // Map* metric_ton_map = new_map();
    // double metric_ton_to_mg = 1000000000;
    // m_put(metric_ton_map, "mg", &metric_ton_to_mg);
    // double metric_ton_to_g = 1000000;
    // m_put(metric_ton_map, "g", &metric_ton_to_g);
    // double metric_ton_to_kg = 1000;
    // m_put(metric_ton_map, "kg", &metric_ton_to_kg);
    // double metric_ton_to_oz = 35274;
    // m_put(metric_ton_map, "oz", &metric_ton_to_oz);
    // double metric_ton_to_lb = 2204.62;
    // m_put(metric_ton_map, "lb", &metric_ton_to_lb);
    // double metric_ton_to_us_ton = 1.10231;
    // m_put(metric_ton_map, "us_ton", &metric_ton_to_us_ton);
    // Unit metric_ton = {
    //     "metric_ton",
    //     metric_ton_map
    // };
    // l_push(units, &metric_ton);

    // // oz
    // Map* oz_map = new_map();
    // double oz_to_mg = 28349.5;
    // m_put(oz_map, "mg", &oz_to_mg);
    // double oz_to_g = 28.3495;
    // m_put(oz_map, "g", &oz_to_g);
    // double oz_to_kg = 0.0283495;
    // m_put(oz_map, "kg", &oz_to_kg);
    // double oz_to_metric_ton = 0.00002835;
    // m_put(oz_map, "metric_ton", &oz_to_metric_ton);
    // double oz_to_lb = 0.0625;
    // m_put(oz_map, "lb", &oz_to_lb);
    // double oz_to_us_ton = 0.00003125;
    // m_put(oz_map, "us_ton", &oz_to_us_ton);
    // Unit oz = {
    //     "oz",
    //     oz_map
    // };
    // l_push(units, &oz);

    // // lb
    // Map* lb_map = new_map();
    // double lb_to_mg = 453592;
    // m_put(lb_map, "mg", &lb_to_mg);
    // double lb_to_g = 453.592;
    // m_put(lb_map, "g", &lb_to_g);
    // double lb_to_kg = 0.453592;
    // m_put(lb_map, "kg", &lb_to_kg);
    // double lb_to_metric_ton = 0.000453592;
    // m_put(lb_map, "metric_ton", &lb_to_metric_ton);
    // double lb_to_oz = 16;
    // m_put(lb_map, "oz", &lb_to_oz);
    // double lb_to_us_ton = 0.0005;
    // m_put(lb_map, "us_ton", &lb_to_us_ton);
    // Unit lb = {
    //     "lb",
    //     lb_map
    // };
    // l_push(units, &lb);

    // // us_ton
    // Map* us_ton_map = new_map();
    // double us_ton_to_mg = 907200000;
    // m_put(us_ton_map, "mg", &us_ton_to_mg);
    // double us_ton_to_g = 907185;
    // m_put(us_ton_map, "g", &us_ton_to_g);
    // double us_ton_to_kg = 907.185;
    // m_put(us_ton_map, "kg", &us_ton_to_kg);
    // double us_ton_to_metric_ton = 0.907185;
    // m_put(us_ton_map, "metric_ton", &us_ton_to_metric_ton);
    // double us_ton_to_oz = 32000;
    // m_put(us_ton_map, "oz", &us_ton_to_oz);
    // double us_ton_to_lb = 2000;
    // m_put(us_ton_map, "lb", &us_ton_to_lb);
    // Unit us_ton = {
    //     "us_ton",
    //     us_ton_map
    // };
    // l_push(units, &us_ton);
}

void define_volume_units(List* units) {



    // l
    Map* l_map = new_map();
    double l_to_ml = 1000;
    m_put(l_map, "ml", &l_to_ml);
    double l_to_l = 1000;
    m_put(l_map, "l", &l_to_l);
    double l_to_fl_oz = 128 / 3.785411784;
    m_put(l_map, "fl_oz", &l_to_fl_oz);
    double l_to_teaspoon = 768 / 3.785411784;
    m_put(l_map, "teaspoon", &l_to_teaspoon);
    double l_to_tablespoon = 256 / 3.785411784;
    m_put(l_map, "tablespoon", &l_to_tablespoon);
    double l_to_cup = 16 / 3.785411784;
    m_put(l_map, "cup", &l_to_cup);
    double l_to_pint = 8 / 3.785411784;
    m_put(l_map, "pint", &l_to_pint);
    double l_to_quart = 4 / 3.785411784;
    m_put(l_map, "quart", &l_to_quart);
    double l_to_gal = 1 / 3.785411784;
    m_put(l_map, "gal", &l_to_gal);
    double l_to_cm3 = 1000;
    m_put(l_map, "cm3", &l_to_cm3);
    double l_to_m3 = 0.001;
    m_put(l_map, "m3", &l_to_m3);
    double l_to_in3 = 1000 / 16.387064;
    m_put(l_map, "in3", &l_to_in3);
    double l_to_ft3 = 1000 / 28316.846592;
    m_put(l_map, "ft3", &l_to_ft3);
    Unit l = {
        "l",
        l_map
    };
    l_push(units, &l);






    // // ml
    // Map* ml_map = new_map();
    // double ml_to_l = 0.001;
    // m_put(ml_map, "l", &ml_to_l);
    // double ml_to_fl_oz = 0.033814;
    // m_put(ml_map, "fl_oz", &ml_to_fl_oz);
    // double ml_to_teaspoon = 0.202884;
    // m_put(ml_map, "teaspoon", &ml_to_teaspoon);
    // double ml_to_tablespoon = 0.067628;
    // m_put(ml_map, "tablespoon", &ml_to_tablespoon);
    // double ml_to_cup = 0.00416667;
    // m_put(ml_map, "cup", &ml_to_cup);
    // double ml_to_pint = 0.00211338;
    // m_put(ml_map, "pint", &ml_to_pint);
    // double ml_to_quart = 0.00105669;
    // m_put(ml_map, "quart", &ml_to_quart);
    // double ml_to_gal = 0.000264172;
    // m_put(ml_map, "gal", &ml_to_gal);
    // double ml_to_cm3 = 1;
    // m_put(ml_map, "cm3", &ml_to_cm3);
    // double ml_to_m3 = 0.000001;
    // m_put(ml_map, "m3", &ml_to_m3);
    // double ml_to_in3 = 0.0610237;
    // m_put(ml_map, "in3", &ml_to_in3);
    // double ml_to_ft3 = 0.000035315;
    // m_put(ml_map, "ft3", &ml_to_ft3);
    // Unit ml = {
    //     "ml",
    //     ml_map
    // };
    // l_push(units, &ml);

    // // l
    // Map* l_map = new_map();
    // double l_to_ml = 1000;
    // m_put(l_map, "ml", &l_to_ml);
    // double l_to_fl_oz = 33.814;
    // m_put(l_map, "fl_oz", &l_to_fl_oz);
    // double l_to_teaspoon = 202.884;
    // m_put(l_map, "teaspoon", &l_to_teaspoon);
    // double l_to_tablespoon = 67.628;
    // m_put(l_map, "tablespoon", &l_to_tablespoon);
    // double l_to_cup = 4.16667;
    // m_put(l_map, "cup", &l_to_cup);
    // double l_to_pint = 2.11338;
    // m_put(l_map, "pint", &l_to_pint);
    // double l_to_quart = 1.05669;
    // m_put(l_map, "quart", &l_to_quart);
    // double l_to_gal = 0.264172;
    // m_put(l_map, "gal", &l_to_gal);
    // double l_to_cm3 = 1000;
    // m_put(l_map, "cm3", &l_to_cm3);
    // double l_to_m3 = 0.001;
    // m_put(l_map, "m3", &l_to_m3);
    // double l_to_in3 = 61.0237;
    // m_put(l_map, "in3", &l_to_in3);
    // double l_to_ft3 = 0.0353147;
    // m_put(l_map, "ft3", &l_to_ft3);
    // Unit l = {
    //     "l",
    //     l_map
    // };
    // l_push(units, &l);

    // // fl_oz
    // Map* fl_oz_map = new_map();
    // double fl_oz_to_ml = 29.5735;
    // m_put(fl_oz_map, "ml", &fl_oz_to_ml);
    // double fl_oz_to_l = 0.0295735;
    // m_put(fl_oz_map, "l", &fl_oz_to_l);
    // double fl_oz_to_teaspoon = 6;
    // m_put(fl_oz_map, "teaspoon", &fl_oz_to_teaspoon);
    // double fl_oz_to_tablespoon = 2;
    // m_put(fl_oz_map, "tablespoon", &fl_oz_to_tablespoon);
    // double fl_oz_to_cup = 0.123223;
    // m_put(fl_oz_map, "cup", &fl_oz_to_cup);
    // double fl_oz_to_pint = 0.0625;
    // m_put(fl_oz_map, "pint", &fl_oz_to_pint);
    // double fl_oz_to_quart = 0.03125;
    // m_put(fl_oz_map, "quart", &fl_oz_to_quart);
    // double fl_oz_to_gal = 0.0078125;
    // m_put(fl_oz_map, "gal", &fl_oz_to_gal);
    // double fl_oz_to_cm3 = 29.5735;
    // m_put(fl_oz_map, "cm3", &fl_oz_to_cm3);
    // double fl_oz_to_m3 = 0.000029574;
    // m_put(fl_oz_map, "m3", &fl_oz_to_m3);
    // double fl_oz_to_in3 = 1.80469;
    // m_put(fl_oz_map, "in3", &fl_oz_to_in3);
    // double fl_oz_to_ft3 = 0.00104438;
    // m_put(fl_oz_map, "ft3", &fl_oz_to_ft3);
    // Unit fl_oz = {
    //     "fl_oz",
    //     fl_oz_map
    // };
    // l_push(units, &fl_oz);

    // // teaspoon
    // Map* teaspoon_map = new_map();
    // double teaspoon_to_ml = 4.92892;
    // m_put(teaspoon_map, "ml", &teaspoon_to_ml);
    // double teaspoon_to_l = 0.00492892;
    // m_put(teaspoon_map, "l", &teaspoon_to_l);
    // double teaspoon_to_fl_oz = 0.166667;
    // m_put(teaspoon_map, "fl_oz", &teaspoon_to_fl_oz);
    // double teaspoon_to_tablespoon = 0.333333;
    // m_put(teaspoon_map, "tablespoon", &teaspoon_to_tablespoon);
    // double teaspoon_to_cup = 0.0205372;
    // m_put(teaspoon_map, "cup", &teaspoon_to_cup);
    // double teaspoon_to_pint = 0.0104167;
    // m_put(teaspoon_map, "pint", &teaspoon_to_pint);
    // double teaspoon_to_quart = 0.00520833;
    // m_put(teaspoon_map, "quart", &teaspoon_to_quart);
    // double teaspoon_to_gal = 0.00130208;
    // m_put(teaspoon_map, "gal", &teaspoon_to_gal);
    // double teaspoon_to_cm3 = 4.92892;
    // m_put(teaspoon_map, "cm3", &teaspoon_to_cm3);
    // double teaspoon_to_m3 = 0.0000049289;
    // m_put(teaspoon_map, "m3", &teaspoon_to_m3);
    // double teaspoon_to_in3 = 0.300781;
    // m_put(teaspoon_map, "in3", &teaspoon_to_in3);
    // double teaspoon_to_ft3 = 0.000174063;
    // m_put(teaspoon_map, "ft3", &teaspoon_to_ft3);
    // Unit teaspoon = {
    //     "teaspoon",
    //     teaspoon_map
    // };
    // l_push(units, &teaspoon);

    // // tablespoon
    // Map* tablespoon_map = new_map();
    // double tablespoon_to_ml = 14.7868;
    // m_put(tablespoon_map, "ml", &tablespoon_to_ml);
    // double tablespoon_to_l = 0.0147868;
    // m_put(tablespoon_map, "l", &tablespoon_to_l);
    // double tablespoon_to_fl_oz = 0.5;
    // m_put(tablespoon_map, "fl_oz", &tablespoon_to_fl_oz);
    // double tablespoon_to_teaspoon = 3;
    // m_put(tablespoon_map, "teaspoon", &tablespoon_to_teaspoon);
    // double tablespoon_to_cup = 0.0616115;
    // m_put(tablespoon_map, "cup", &tablespoon_to_cup);
    // double tablespoon_to_pint = 0.03125;
    // m_put(tablespoon_map, "pint", &tablespoon_to_pint);
    // double tablespoon_to_quart = 0.015625;
    // m_put(tablespoon_map, "quart", &tablespoon_to_quart);
    // double tablespoon_to_gal = 0.00390625;
    // m_put(tablespoon_map, "gal", &tablespoon_to_gal);
    // double tablespoon_to_cm3 = 14.7868;
    // m_put(tablespoon_map, "cm3", &tablespoon_to_cm3);
    // double tablespoon_to_m3 = 0.000014787;
    // m_put(tablespoon_map, "m3", &tablespoon_to_m3);
    // double tablespoon_to_in3 = 0.902344;
    // m_put(tablespoon_map, "in3", &tablespoon_to_in3);
    // double tablespoon_to_ft3 = 0.00052219;
    // m_put(tablespoon_map, "ft3", &tablespoon_to_ft3);
    // Unit tablespoon = {
    //     "tablespoon",
    //     tablespoon_map
    // };
    // l_push(units, &tablespoon);

    // // cup
    // Map* cup_map = new_map();
    // double cup_to_ml = 240;
    // m_put(cup_map, "ml", &cup_to_ml);
    // double cup_to_l = 0.24;
    // m_put(cup_map, "l", &cup_to_l);
    // double cup_to_fl_oz = 8.11537;
    // m_put(cup_map, "fl_oz", &cup_to_fl_oz);
    // double cup_to_teaspoon = 48.6922;
    // m_put(cup_map, "teaspoon", &cup_to_teaspoon);
    // double cup_to_tablespoon = 16.2307;
    // m_put(cup_map, "tablespoon", &cup_to_tablespoon);
    // double cup_to_pint = 0.50721;
    // m_put(cup_map, "pint", &cup_to_pint);
    // double cup_to_quart = 0.253605;
    // m_put(cup_map, "quart", &cup_to_quart);
    // double cup_to_gal = 0.0634013;
    // m_put(cup_map, "gal", &cup_to_gal);
    // double cup_to_cm3 = 240;
    // m_put(cup_map, "cm3", &cup_to_cm3);
    // double cup_to_m3 = 0.00024;
    // m_put(cup_map, "m3", &cup_to_m3);
    // double cup_to_in3 = 14.6457;
    // m_put(cup_map, "in3", &cup_to_in3);
    // double cup_to_ft3 = 0.00847552;
    // m_put(cup_map, "ft3", &cup_to_ft3);
    // Unit cup = {
    //     "cup",
    //     cup_map
    // };
    // l_push(units, &cup);

    // // pint
    // Map* pint_map = new_map();
    // double pint_to_ml = 473.176;
    // m_put(pint_map, "ml", &pint_to_ml);
    // double pint_to_l = 0.473176;
    // m_put(pint_map, "l", &pint_to_l);
    // double pint_to_fl_oz = 16;
    // m_put(pint_map, "fl_oz", &pint_to_fl_oz);
    // double pint_to_teaspoon = 96;
    // m_put(pint_map, "teaspoon", &pint_to_teaspoon);
    // double pint_to_tablespoon = 32;
    // m_put(pint_map, "tablespoon", &pint_to_tablespoon);
    // double pint_to_cup = 1.97157;
    // m_put(pint_map, "cup", &pint_to_cup);
    // double pint_to_quart = 0.5;
    // m_put(pint_map, "quart", &pint_to_quart);
    // double pint_to_gal = 0.125;
    // m_put(pint_map, "gal", &pint_to_gal);
    // double pint_to_cm3 = 473.176;
    // m_put(pint_map, "cm3", &pint_to_cm3);
    // double pint_to_m3 = 0.000473176;
    // m_put(pint_map, "m3", &pint_to_m3);
    // double pint_to_in3 = 28.875;
    // m_put(pint_map, "in3", &pint_to_in3);
    // double pint_to_ft3 = 0.0167101;
    // m_put(pint_map, "ft3", &pint_to_ft3);
    // Unit pint = {
    //     "pint",
    //     pint_map
    // };
    // l_push(units, &pint);

    // // quart
    // Map* quart_map = new_map();
    // double quart_to_ml = 946.353;
    // m_put(quart_map, "ml", &quart_to_ml);
    // double quart_to_l = 0.946353;
    // m_put(quart_map, "l", &quart_to_l);
    // double quart_to_fl_oz = 32;
    // m_put(quart_map, "fl_oz", &quart_to_fl_oz);
    // double quart_to_teaspoon = 192;
    // m_put(quart_map, "teaspoon", &quart_to_teaspoon);
    // double quart_to_tablespoon = 64;
    // m_put(quart_map, "tablespoon", &quart_to_tablespoon);
    // double quart_to_cup = 3.94314;
    // m_put(quart_map, "cup", &quart_to_cup);
    // double quart_to_pint = 2;
    // m_put(quart_map, "pint", &quart_to_pint);
    // double quart_to_gal = 0.25;
    // m_put(quart_map, "gal", &quart_to_gal);
    // double quart_to_cm3 = 946.353;
    // m_put(quart_map, "cm3", &quart_to_cm3);
    // double quart_to_m3 = 0.000946353;
    // m_put(quart_map, "m3", &quart_to_m3);
    // double quart_to_in3 = 57.75;
    // m_put(quart_map, "in3", &quart_to_in3);
    // double quart_to_ft3 = 0.0334201;
    // m_put(quart_map, "ft3", &quart_to_ft3);
    // Unit quart = {
    //     "quart",
    //     quart_map
    // };
    // l_push(units, &quart);

    // // gal
    // Map* gal_map = new_map();
    // double gal_to_ml = 3785.41;
    // m_put(gal_map, "ml", &gal_to_ml);
    // double gal_to_l = 3.78541;
    // m_put(gal_map, "l", &gal_to_l);
    // double gal_to_fl_oz = 128;
    // m_put(gal_map, "fl_oz", &gal_to_fl_oz);
    // double gal_to_teaspoon = 768;
    // m_put(gal_map, "teaspoon", &gal_to_teaspoon);
    // double gal_to_tablespoon = 256;
    // m_put(gal_map, "tablespoon", &gal_to_tablespoon);
    // double gal_to_cup = 15.7725;
    // m_put(gal_map, "cup", &gal_to_cup);
    // double gal_to_pint = 8;
    // m_put(gal_map, "pint", &gal_to_pint);
    // double gal_to_quart = 4;
    // m_put(gal_map, "quart", &gal_to_quart);
    // double gal_to_cm3 = 3785.41;
    // m_put(gal_map, "cm3", &gal_to_cm3);
    // double gal_to_m3 = 0.00378541;
    // m_put(gal_map, "m3", &gal_to_m3);
    // double gal_to_in3 = 231;
    // m_put(gal_map, "in3", &gal_to_in3);
    // double gal_to_ft3 = 0.133681;
    // m_put(gal_map, "ft3", &gal_to_ft3);
    // Unit gal = {
    //     "gal",
    //     gal_map
    // };
    // l_push(units, &gal);

    // // cm3
    // Map* cm3_map = new_map();
    // double cm3_to_ml = 1;
    // m_put(cm3_map, "ml", &cm3_to_ml);
    // double cm3_to_l = 0.001;
    // m_put(cm3_map, "l", &cm3_to_l);
    // double cm3_to_fl_oz = 0.033814;
    // m_put(cm3_map, "fl_oz", &cm3_to_fl_oz);
    // double cm3_to_teaspoon = 0.202884;
    // m_put(cm3_map, "teaspoon", &cm3_to_teaspoon);
    // double cm3_to_tablespoon = 0.067628;
    // m_put(cm3_map, "tablespoon", &cm3_to_tablespoon);
    // double cm3_to_cup = 0.00416667;
    // m_put(cm3_map, "cup", &cm3_to_cup);
    // double cm3_to_pint = 0.00211338;
    // m_put(cm3_map, "pint", &cm3_to_pint);
    // double cm3_to_quart = 0.00105669;
    // m_put(cm3_map, "quart", &cm3_to_quart);
    // double cm3_to_gal = 0.000264172;
    // m_put(cm3_map, "gal", &cm3_to_gal);
    // double cm3_to_m3 = 0.000001;
    // m_put(cm3_map, "m3", &cm3_to_m3);
    // double cm3_to_in3 = 0.0610237;
    // m_put(cm3_map, "in3", &cm3_to_in3);
    // double cm3_to_ft3 = 0.000035315;
    // m_put(cm3_map, "ft3", &cm3_to_ft3);
    // Unit cm3 = {
    //     "cm3",
    //     cm3_map
    // };
    // l_push(units, &cm3);

    // // m3
    // Map* m3_map = new_map();
    // double m3_to_ml = 1000000;
    // m_put(m3_map, "ml", &m3_to_ml);
    // double m3_to_l = 1000;
    // m_put(m3_map, "l", &m3_to_l);
    // double m3_to_fl_oz = 33814;
    // m_put(m3_map, "fl_oz", &m3_to_fl_oz);
    // double m3_to_teaspoon = 202884;
    // m_put(m3_map, "teaspoon", &m3_to_teaspoon);
    // double m3_to_tablespoon = 67628;
    // m_put(m3_map, "tablespoon", &m3_to_tablespoon);
    // double m3_to_cup = 4166.67;
    // m_put(m3_map, "cup", &m3_to_cup);
    // double m3_to_pint = 2113.38;
    // m_put(m3_map, "pint", &m3_to_pint);
    // double m3_to_quart = 1056.69;
    // m_put(m3_map, "quart", &m3_to_quart);
    // double m3_to_gal = 264.172;
    // m_put(m3_map, "gal", &m3_to_gal);
    // double m3_to_cm3 = 1000000;
    // m_put(m3_map, "cm3", &m3_to_cm3);
    // double m3_to_in3 = 61023.7;
    // m_put(m3_map, "in3", &m3_to_in3);
    // double m3_to_ft3 = 168936;
    // m_put(m3_map, "ft3", &m3_to_ft3);
    // Unit m3 = {
    //     "m3",
    //     m3_map
    // };
    // l_push(units, &m3);

    // // in3
    // Map* in3_map = new_map();
    // double in3_to_ml = 16.3871;
    // m_put(in3_map, "ml", &in3_to_ml);
    // double in3_to_l = 0.0163871;
    // m_put(in3_map, "l", &in3_to_l);
    // double in3_to_fl_oz = 0.554113;
    // m_put(in3_map, "fl_oz", &in3_to_fl_oz);
    // double in3_to_teaspoon = 3.32468;
    // m_put(in3_map, "teaspoon", &in3_to_teaspoon);
    // double in3_to_tablespoon = 1.10823;
    // m_put(in3_map, "tablespoon", &in3_to_tablespoon);
    // double in3_to_cup = 0.0682794;
    // m_put(in3_map, "cup", &in3_to_cup);
    // double in3_to_pint = 0.034632;
    // m_put(in3_map, "pint", &in3_to_pint);
    // double in3_to_quart = 0.017316;
    // m_put(in3_map, "quart", &in3_to_quart);
    // double in3_to_gal = 0.004329;
    // m_put(in3_map, "gal", &in3_to_gal);
    // double in3_to_cm3 = 16.3871;
    // m_put(in3_map, "cm3", &in3_to_cm3);
    // double in3_to_m3 = 0.000016387;
    // m_put(in3_map, "m3", &in3_to_m3);
    // double in3_to_ft3 = 0.000578704;
    // m_put(in3_map, "ft3", &in3_to_ft3);
    // Unit in3 = {
    //     "in3",
    //     in3_map
    // };
    // l_push(units, &in3);

    // // ft3
    // Map* ft3_map = new_map();
    // double ft3_to_ml = 28316.8;
    // m_put(ft3_map, "ml", &ft3_to_ml);
    // double ft3_to_l = 28.3168;
    // m_put(ft3_map, "l", &ft3_to_l);
    // double ft3_to_fl_oz = 957.506;
    // m_put(ft3_map, "fl_oz", &ft3_to_fl_oz);
    // double ft3_to_teaspoon = 5745.04;
    // m_put(ft3_map, "teaspoon", &ft3_to_teaspoon);
    // double ft3_to_tablespoon = 1915.01;
    // m_put(ft3_map, "tablespoon", &ft3_to_tablespoon);
    // double ft3_to_cup = 117.987;
    // m_put(ft3_map, "cup", &ft3_to_cup);
    // double ft3_to_pint = 59.8442;
    // m_put(ft3_map, "pint", &ft3_to_pint);
    // double ft3_to_quart = 29.9221;
    // m_put(ft3_map, "quart", &ft3_to_quart);
    // double ft3_to_gal = 7.48052;
    // m_put(ft3_map, "gal", &ft3_to_gal);
    // double ft3_to_cm3 = 28316.8;
    // m_put(ft3_map, "cm3", &ft3_to_cm3);
    // double ft3_to_m3 = 0.0283168;
    // m_put(ft3_map, "m3", &ft3_to_m3);
    // double ft3_to_in3 = 1728;
    // m_put(ft3_map, "in3", &ft3_to_in3);
    // Unit ft3 = {
    //     "ft3",
    //     ft3_map
    // };
    // l_push(units, &ft3);

}

void define_area_units(List* units) {

    // m2
    Map* m2_map = new_map();
    double m2_to_cm2 = 10000;
    m_put(m2_map, "cm2", &m2_to_cm2);
    double m2_to_m2 = 1;
    m_put(m2_map, "m2", &m2_to_m2);
    double m2_to_hectare = 0.0001;
    m_put(m2_map, "hectare", &m2_to_hectare);
    double m2_to_km2 = 0.000001;
    m_put(m2_map, "km2", &m2_to_km2);
    double m2_to_in2 = (1 / 0.0254) * (1 / 0.0254);//1550;
    m_put(m2_map, "in2", &m2_to_in2);
    double m2_to_ft2 = (1 / (0.0254 * 12)) * (1 / (0.0254 * 12));// 10.7639;
    m_put(m2_map, "ft2", &m2_to_ft2);
    double m2_to_yard2 = (1 / (0.0254 * 36)) * (1 / (0.0254 * 36));//1.19599;
    m_put(m2_map, "yard2", &m2_to_yard2);
    double m2_to_mile2 = (1 / (0.0254 * 12 * 5280)) * (1 / (0.0254 * 12 * 5280));//0.0000003861;
    m_put(m2_map, "mile2", &m2_to_mile2);
    double m2_to_acre = m2_to_ft2 / 43560;//0.000247105;
    m_put(m2_map, "acre", &m2_to_acre);
    Unit m2 = {
        "m2",
        m2_map
    };
    l_push(units, &m2);

    //1 inch = 2.54 cm exactly
    //1 inch = 0.0254 m exactly
    // 1 m = 1 / 0.0254 in
    // 1 m = 1 / (0.0254 * 12) ft
    // 1 m = 1 / (0.0254 * 36) yard
    // 1 m = 1 / (0.0254 * 12 * 5280) mile

    // // cm2
    // Map* cm2_map = new_map();
    // double cm2_to_m2 = 0.0001;
    // m_put(cm2_map, "m2", &cm2_to_m2);
    // double cm2_to_hectare = 0.00000001;
    // m_put(cm2_map, "hectare", &cm2_to_hectare);
    // double cm2_to_km2 = 0.0000000001;
    // m_put(cm2_map, "km2", &cm2_to_km2);
    // double cm2_to_in2 = 0.155;
    // m_put(cm2_map, "in2", &cm2_to_in2);
    // double cm2_to_ft2 = 0.00107639;
    // m_put(cm2_map, "ft2", &cm2_to_ft2);
    // double cm2_to_yard2 = 0.000119599;
    // m_put(cm2_map, "yard2", &cm2_to_yard2);
    // double cm2_to_mile2 = 0.00000000003861;
    // m_put(cm2_map, "mile2", &cm2_to_mile2);
    // double cm2_to_acre = 0.000000024711;
    // m_put(cm2_map, "acre", &cm2_to_acre);
    // Unit cm2 = {
    //     "cm2",
    //     cm2_map
    // };
    // l_push(units, &cm2);

    // // m2
    // Map* m2_map = new_map();
    // double m2_to_cm2 = 10000;
    // m_put(m2_map, "cm2", &m2_to_cm2);
    // double m2_to_hectare = 0.0001;
    // m_put(m2_map, "hectare", &m2_to_hectare);
    // double m2_to_km2 = 0.000001;
    // m_put(m2_map, "km2", &m2_to_km2);
    // double m2_to_in2 = 1550;
    // m_put(m2_map, "in2", &m2_to_in2);
    // double m2_to_ft2 = 10.7639;
    // m_put(m2_map, "ft2", &m2_to_ft2);
    // double m2_to_yard2 = 1.19599;
    // m_put(m2_map, "yard2", &m2_to_yard2);
    // double m2_to_mile2 = 0.0000003861;
    // m_put(m2_map, "mile2", &m2_to_mile2);
    // double m2_to_acre = 0.000247105;
    // m_put(m2_map, "acre", &m2_to_acre);
    // Unit m2 = {
    //     "m2",
    //     m2_map
    // };
    // l_push(units, &m2);

    // // hectare
    // Map* hectare_map = new_map();
    // double hectare_to_cm2 = 100000000;
    // m_put(hectare_map, "cm2", &hectare_to_cm2);
    // double hectare_to_m2 = 10000;
    // m_put(hectare_map, "m2", &hectare_to_m2);
    // double hectare_to_km2 = 0.01;
    // m_put(hectare_map, "km2", &hectare_to_km2);
    // double hectare_to_in2 = 15500000;
    // m_put(hectare_map, "in2", &hectare_to_in2);
    // double hectare_to_ft2 = 107639;
    // m_put(hectare_map, "ft2", &hectare_to_ft2);
    // double hectare_to_yard2 = 11959.9;
    // m_put(hectare_map, "yard2", &hectare_to_yard2);
    // double hectare_to_mile2 = 0.00386102;
    // m_put(hectare_map, "mile2", &hectare_to_mile2);
    // double hectare_to_acre = 2.47105;
    // m_put(hectare_map, "acre", &hectare_to_acre);
    // Unit hectare = {
    //     "hectare",
    //     hectare_map
    // };
    // l_push(units, &hectare);

    // // km2
    // Map* km2_map = new_map();
    // double km2_to_cm2 = 10000000000;
    // m_put(km2_map, "cm2", &km2_to_cm2);
    // double km2_to_m2 = 1000000;
    // m_put(km2_map, "m2", &km2_to_m2);
    // double km2_to_hectare = 100;
    // m_put(km2_map, "hectare", &km2_to_hectare);
    // double km2_to_in2 = 1550000000;
    // m_put(km2_map, "in2", &km2_to_in2);
    // double km2_to_ft2 = 10760000;
    // m_put(km2_map, "ft2", &km2_to_ft2);
    // double km2_to_yard2 = 1196000;
    // m_put(km2_map, "yard2", &km2_to_yard2);
    // double km2_to_mile2 = 0.386102;
    // m_put(km2_map, "mile2", &km2_to_mile2);
    // double km2_to_acre = 247.105;
    // m_put(km2_map, "acre", &km2_to_acre);
    // Unit km2 = {
    //     "km2",
    //     km2_map
    // };
    // l_push(units, &km2);

    // // in2
    // Map* in2_map = new_map();
    // double in2_to_cm2 = 6.4516;
    // m_put(in2_map, "cm2", &in2_to_cm2);
    // double in2_to_m2 = 0.00064516;
    // m_put(in2_map, "m2", &in2_to_m2);
    // double in2_to_hectare = 0.000000064516;
    // m_put(in2_map, "hectare", &in2_to_hectare);
    // double in2_to_km2 = 0.00000000064516;
    // m_put(in2_map, "km2", &in2_to_km2);
    // double in2_to_ft2 = 0.00694444;
    // m_put(in2_map, "ft2", &in2_to_ft2);
    // double in2_to_yard2 = 0.000771605;
    // m_put(in2_map, "yard2", &in2_to_yard2);
    // double in2_to_mile2 = 0.0000000002491;
    // m_put(in2_map, "mile2", &in2_to_mile2);
    // double in2_to_acre = 0.00000015942;
    // m_put(in2_map, "acre", &in2_to_acre);
    // Unit in2 = {
    //     "in2",
    //     in2_map
    // };
    // l_push(units, &in2);

    // // ft2
    // Map* ft2_map = new_map();
    // double ft2_to_cm2 = 929.03;
    // m_put(ft2_map, "cm2", &ft2_to_cm2);
    // double ft2_to_m2 = 0.092903;
    // m_put(ft2_map, "m2", &ft2_to_m2);
    // double ft2_to_hectare = 0.0000092903;
    // m_put(ft2_map, "hectare", &ft2_to_hectare);
    // double ft2_to_km2 = 0.000000092903;
    // m_put(ft2_map, "km2", &ft2_to_km2);
    // double ft2_to_in2 = 144;
    // m_put(ft2_map, "in2", &ft2_to_in2);
    // double ft2_to_yard2 = 0.111111;
    // m_put(ft2_map, "yard2", &ft2_to_yard2);
    // double ft2_to_mile2 = 0.00000003587;
    // m_put(ft2_map, "mile2", &ft2_to_mile2);
    // double ft2_to_acre = 0.000022957;
    // m_put(ft2_map, "acre", &ft2_to_acre);
    // Unit ft2 = {
    //     "ft2",
    //     ft2_map
    // };
    // l_push(units, &ft2);

    // // yard2
    // Map* yard2_map = new_map();
    // double yard2_to_cm2 = 8361.27;
    // m_put(yard2_map, "cm2", &yard2_to_cm2);
    // double yard2_to_m2 = 0.836127;
    // m_put(yard2_map, "m2", &yard2_to_m2);
    // double yard2_to_hectare = 0.000083613;
    // m_put(yard2_map, "hectare", &yard2_to_hectare);
    // double yard2_to_km2 = 0.00000083613;
    // m_put(yard2_map, "km2", &yard2_to_km2);
    // double yard2_to_in2 = 1296;
    // m_put(yard2_map, "in2", &yard2_to_in2);
    // double yard2_to_ft2 = 9;
    // m_put(yard2_map, "ft2", &yard2_to_ft2);
    // double yard2_to_mile2 = 0.00000032283;
    // m_put(yard2_map, "mile2", &yard2_to_mile2);
    // double yard2_to_acre = 0.000206612;
    // m_put(yard2_map, "acre", &yard2_to_acre);
    // Unit yard2 = {
    //     "yard2",
    //     yard2_map
    // };
    // l_push(units, &yard2);

    // // mile2
    // Map* mile2_map = new_map();
    // double mile2_to_cm2 = 25899900000;
    // m_put(mile2_map, "cm2", &mile2_to_cm2);
    // double mile2_to_m2 = 2589990;
    // m_put(mile2_map, "m2", &mile2_to_m2);
    // double mile2_to_hectare = 258.999;
    // m_put(mile2_map, "hectare", &mile2_to_hectare);
    // double mile2_to_km2 = 2.58999;
    // m_put(mile2_map, "km2", &mile2_to_km2);
    // double mile2_to_in2 = 4014000000;
    // m_put(mile2_map, "in2", &mile2_to_in2);
    // double mile2_to_ft2 = 27880000;
    // m_put(mile2_map, "ft2", &mile2_to_ft2);
    // double mile2_to_yard2 = 3098000;
    // m_put(mile2_map, "yard2", &mile2_to_yard2);
    // double mile2_to_acre = 640;
    // m_put(mile2_map, "acre", &mile2_to_acre);
    // Unit mile2 = {
    //     "mile2",
    //     mile2_map
    // };
    // l_push(units, &mile2);

    // // acre
    // Map* acre_map = new_map();
    // double acre_to_cm2 = 40470000;
    // m_put(acre_map, "cm2", &acre_to_cm2);
    // double acre_to_m2 = 4046.86;
    // m_put(acre_map, "m2", &acre_to_m2);
    // double acre_to_hectare = 0.404686;
    // m_put(acre_map, "hectare", &acre_to_hectare);
    // double acre_to_km2 = 0.00404686;
    // m_put(acre_map, "km2", &acre_to_km2);
    // double acre_to_in2 = 6273000;
    // m_put(acre_map, "in2", &acre_to_in2);
    // double acre_to_ft2 = 43560;
    // m_put(acre_map, "ft2", &acre_to_ft2);
    // double acre_to_yard2 = 4840;
    // m_put(acre_map, "yard2", &acre_to_yard2);
    // double acre_to_mile2 = 0.0015625;
    // m_put(acre_map, "mile2", &acre_to_mile2);
    // Unit acre = {
    //     "acre",
    //     acre_map
    // };
    // l_push(units, &acre);

}

void define_time_units(List* units) {

    // ms
    Map* ms_map = new_map();
    double ms_to_ps = 1000000000;
    m_put(ms_map, "ps", &ms_to_ps);
    double ms_to_ns = 1000000;
    m_put(ms_map, "ns", &ms_to_ns);
    double ms_to_ms = 1;
    m_put(ms_map, "ms", &ms_to_ms);
    double ms_to_s = 0.0001;
    m_put(ms_map, "s", &ms_to_s);
    double ms_to_min = ms_to_s / 60;
    m_put(ms_map, "min", &ms_to_min);
    double ms_to_hour = ms_to_s / 60;
    m_put(ms_map, "hour", &ms_to_hour);
    double ms_to_day = ms_to_hour / 24;
    m_put(ms_map, "day", &ms_to_day);
    double ms_to_week = ms_to_day / 7;
    m_put(ms_map, "week", &ms_to_week);
    double ms_to_year = ms_to_day / 365.242190419;
    m_put(ms_map, "year", &ms_to_year);
    double ms_to_month = ms_to_year * 12;
    m_put(ms_map, "month", &ms_to_month);
    Unit ms = {
        "ms",
        ms_map
    };
    l_push(units, &ms);
}

void define_speed_units(List* units) {

    // m_s
    Map* m_s_map = new_map();
    double m_s_to_m_s = 1;
    m_put(m_s_map, "m/s", &m_s_to_m_s);
    double m_s_to_mph = (60 * 60) / 1609.344;
    m_put(m_s_map, "mph", &m_s_to_mph);
    double m_s_to_ft_s = 1 / 0.3048;
    m_put(m_s_map, "ft/s", &m_s_to_ft_s);
    double m_s_to_kph = 3.6;
    m_put(m_s_map, "kph", &m_s_to_kph);
    double m_s_to_knot = (60 * 60) / 1852;
    m_put(m_s_map, "knot", &m_s_to_knot);
    Unit m_s = {
        "m_s",
        m_s_map
    };
    l_push(units, &m_s);
}

void define_energy_units(List* units) {

    // kj
    Map* kj_map = new_map();
    double kj_to_kj = 1;
    m_put(kj_map, "kj", &kj_to_kj);
    double kj_to_j = 1000;
    m_put(kj_map, "j", &kj_to_j);
    double kj_to_gcal = 1 / 4.184;
    m_put(kj_map, "gcal", &kj_to_gcal);
    double kj_to_kcal = kj_to_gcal * 1000;
    m_put(kj_map, "kcal", &kj_to_kcal);
    double kj_to_wh = 1000 / 3600;
    m_put(kj_map, "wh", &kj_to_wh);
    double kj_to_kwh = 1000 / 3600000;
    m_put(kj_map, "kwh", &kj_to_kwh);
    double kj_to_eV = 1000 / 0.0000000000000000001602176634;
    m_put(kj_map, "eV", &kj_to_eV);
    double kj_to_BTU = 1 / 105505.585262;
    m_put(kj_map, "BTU", &kj_to_BTU);
    double kj_to_ft_lb = 1000/ (4.4482216152605 * 0.3048);
    m_put(kj_map, "ft·lb", &kj_to_ft_lb);
    Unit kj = {
        "kj",
        kj_map
    };
    l_push(units, &kj);
}

void define_pressure_units(List* units) {

    // Pa
    Map* Pa_map = new_map();
    double Pa_to_Pa = 1;
    m_put(Pa_map, "Pa", &Pa_to_Pa);
    double Pa_to_bar = 0.00001;
    m_put(Pa_map, "bar", &Pa_to_bar);
    double Pa_to_psi = (0.0254 * 0.0254) / 4.4482216152605;
    m_put(Pa_map, "psi", &Pa_to_psi);
    double Pa_to_atm = 1 / 101325;
    m_put(Pa_map, "atm", &Pa_to_atm);
    double Pa_to_torr = 760 / 101325;
    m_put(Pa_map, "torr", &Pa_to_torr);
    Unit Pa = {
        "Pa",
        Pa_map
    };
    l_push(units, &Pa);
}

void define_storage_units(List* units) {

    // gb
    Map* gb_map = new_map();
    double gb_to_bit = 8000000000;
    m_put(gb_map, "bit", &gb_to_bit);
    double gb_to_b = 1000000000;
    m_put(gb_map, "b", &gb_to_b);
    double gb_to_kb = 1000000;
    m_put(gb_map, "kb", &gb_to_kb);
    double gb_to_mb = 1000;
    m_put(gb_map, "mb", &gb_to_mb);
    double gb_to_gb = 1;
    m_put(gb_map, "gb", &gb_to_gb);
    double gb_to_tb = 0.001;
    m_put(gb_map, "tb", &gb_to_tb);
    double gb_to_pb = 0.000001;
    m_put(gb_map, "pb", &gb_to_pb);
    Unit gb = {
        "gb",
        gb_map
    };
    l_push(units, &gb);
}

void define_force_units(List* units) {

    // N
    Map* N_map = new_map();
    double N_to_N = 1;
    m_put(N_map, "N", &N_to_N);
    double N_to_lbf = 1 / 4.4482216152605;
    m_put(N_map, "lbf", &N_to_lbf);
    Unit N = {
        "N",
        N_map
    };
    l_push(units, &N);
}

void print_units(List* units) {
    printf("Units:\n");
    printf("1. m\n");
}


// ansii help
void clear_last_line() {
    printf("\033[1A"); // Move cursor up 1 line
    printf("\033[2K"); // Clear the entire line
    printf("\r");      // Move cursor to the beginning of the line
    fflush(stdout);
}


int TERMINAL_WIDTH, TERMINAL_HEIGHT;
ScreenWriter* screen_writer;

void handle_resize(int sig) {
    sw_get_terminal_dimensions(&TERMINAL_WIDTH, &TERMINAL_HEIGHT);
}

void set_cells(char* value, SWColor background, SWColor text_color, SWCell** cells, int x, int y) {
    int i = x + y * TERMINAL_WIDTH;
    for (int ix = 0; ix < strlen(value); ++ix) {
        if (x + ix < TERMINAL_WIDTH) {
            char cell_char[2];
            cell_char[0] = value[ix];
            cell_char[1] = '\0';
            SWCell cell = {
                cell_char,
                text_color,
                background
            };
            sw_copy_cell(&cell, cells[i + ix]);
        }
    }
}

int main(int argc, char **argv) {

    // resize handler
    signal(SIGWINCH, handle_resize);

    // init
    sw_get_terminal_dimensions(&TERMINAL_WIDTH, &TERMINAL_HEIGHT);
    TERMINAL_HEIGHT--;
    screen_writer = malloc(sizeof(ScreenWriter));
    screen_writer->current_height = TERMINAL_HEIGHT;
    screen_writer->current_width = TERMINAL_WIDTH;


    /*
    rgb(100, 69, 54)
    rgb(178, 103, 94)
    rgb(196, 163, 129)
    rgb(187, 214, 134)
    rgb(238, 241, 189)
    */

    // main loop
    SWCell** cells = malloc(sizeof(SWCell*) * TERMINAL_HEIGHT * TERMINAL_WIDTH);

    SWColor background = {0,0,0};
    SWColor primary = {238, 241, 189};
    SWColor secondary = {196, 163, 129};
    SWColor tercery = {178, 103, 94};

    int last_x = TERMINAL_WIDTH - 1;
    int last_y = TERMINAL_HEIGHT - 1;
    for (int x = 0; x < TERMINAL_WIDTH; ++x) {
        for (int y = 0; y < TERMINAL_HEIGHT; ++y) {
            SWCell* cell = malloc(sizeof(SWCell));
            cell->unicode = strdup(" ");

            if (x == 0 && y == 0) {
                cell->unicode = strdup(HEAVY_DOWN_AND_RIGHT);
            }
            else if (x == 0 && y == last_y) {
                cell->unicode = strdup(HEAVY_UP_AND_RIGHT);
            }
            else if (x == last_x && y == 0) {
                cell->unicode = strdup(HEAVY_DOWN_AND_LEFT);
            }
            else if (x == last_x && y == last_y) {
                cell->unicode = strdup(HEAVY_UP_AND_LEFT);
            }
            else if (x % TERMINAL_WIDTH == 0 || (x+1) % TERMINAL_WIDTH == 0) {
                cell->unicode = strdup(HEAVY_VERTICAL);
            }
            else if (y == 0 || (y+1) == TERMINAL_HEIGHT) {
                cell->unicode = strdup(HEAVY_HORIZONTAL);
            }

            cell->background_color.r = background.r;
            cell->background_color.g = background.g;
            cell->background_color.b = background.b;

            cell->text_color.r = tercery.r;
            cell->text_color.g = tercery.g;
            cell->text_color.b = tercery.b;
            

            int index = x + y * TERMINAL_WIDTH;
            cells[index] = cell;
        }
    }
    
    
    set_cells(
        "value",
        background,
        primary,
        cells,
        4,
        4
    );
    
    set_cells(
        "1",
        background,
        secondary,
        cells,
        20,
        4
    );
    
    set_cells(
        "from",
        background,
        primary,
        cells,
        36,
        4
    );
    
    sw_set_screen(cells, TERMINAL_WIDTH, TERMINAL_HEIGHT, screen_writer);


    // // define units
    // List* units = new_list();
    // define_length_units(units);
    // define_mass_units(units);
    // define_volume_units(units);
    // define_area_units(units);
    // define_time_units(units);
    // define_speed_units(units);
    // define_energy_units(units);
    // define_pressure_units(units);
    // define_storage_units(units);
    // define_force_units(units);


    // // set colors
    // bg_rgb(97, 52, 7);
    // color_rgb(242, 236, 196);
    
    // // get input
    // printf("\nVALUE: %s", ANSI_RESET);
    // double number;
    // scanf("%lf", &number);
    // printf("");

    


    return 0;
}
