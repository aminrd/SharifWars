#include "xmlreader.h"
#include "zombie.h"
#include "player.h"



XmlReader::XmlReader(vector<Player*> players){

    QDomDocument document;
    QFile file("sample.xml");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "failed to open file";
        exit(1);
    }
    else
    {
        if(!document.setContent(&file))
        {
            qDebug() << "Fialed to load file";
            exit(1);
        }
        file.close();
    }


    QDomElement root = document.firstChildElement();

    //    ListEmlenet(root,"cost");

    QDomNodeList teams = root.elementsByTagName("team");

    for(unsigned int i = 1; i < players.size(); i++){

        int id_team=players[i]->getTeam();
        //------------------------------------------------------first selection team
        QDomNode teamnode = teams.at(id_team);
        QDomElement team = teamnode.toElement();

        //------------------------------------------------------name
        QDomNodeList names = team.elementsByTagName("name");
        QDomNode name_node = names.at(0);
        QDomElement name_element = name_node.toElement();
        players[i]->information.team_name=name_element.text();

        //------------------------------------------------------Building

        QDomNodeList buildings=team.elementsByTagName("building");
        for(int j=0; j<buildings.count(); j++){
            QDomNode build=buildings.at(j);
            QDomElement build_element=build.toElement();

            //---------------------------------------------------base Building
            if(build_element.attribute("type")=="base"){

                //----------------------------------------------base name
                QDomNodeList base_names=build_element.elementsByTagName("name");
                QDomNode base_name=base_names.at(0);
                QDomElement base_name_element=base_name.toElement();
                players[i]->information.base_name=base_name_element.text();

                //----------------------------------------------base cost
                QDomNodeList base_costs=build_element.elementsByTagName("cost");
                QDomNode base_cost=base_costs.at(0);
                QDomElement base_cost_element=base_cost.toElement();
                players[i]->information.base_cost=base_cost_element.text().toInt();

                //----------------------------------------------base upgrade_cost
                QDomNodeList base_upgrade_costs=build_element.elementsByTagName("upgrade_cost");
                QDomNode base_upgrade_cost=base_upgrade_costs.at(0);
                QDomElement base_upgrade_cost_element=base_upgrade_cost.toElement();
                players[i]->information.base_upgrade_cost=base_upgrade_cost_element.text().toInt();

                //----------------------------------------------construction time
                QDomNodeList construction_times=build_element.elementsByTagName("construction_time");
                QDomNode construction_time=construction_times.at(0);
                QDomElement construction_time_element=construction_time.toElement();
                players[i]->information.base_time_constructoin=construction_time_element.text().toInt();

                //----------------------------------------------max health
                QDomNodeList max_healths=build_element.elementsByTagName("max_health");
                QDomNode max_health=max_healths.at(0);
                QDomElement max_health_element=max_health.toElement();
                players[i]->information.base_max_health=max_health_element.text().toInt();

                //----------------------------------------------attack_damage
                QDomNodeList attack_damages=build_element.elementsByTagName("attack_damage");
                QDomNode attack_damage=attack_damages.at(0);
                QDomElement attack_damage_element=attack_damage.toElement();
                players[i]->information.base_attack_damage=attack_damage_element.text().toInt();

                //----------------------------------------------attack_range
                QDomNodeList attack_ranges=build_element.elementsByTagName("attack_range");
                QDomNode attack_range=attack_ranges.at(0);
                QDomElement attack_range_element=attack_range.toElement();
                players[i]->information.base_attack_range=attack_range_element.text().toInt();

                //----------------------------------------------attack_delay
                QDomNodeList attack_delays=build_element.elementsByTagName("attack_delay");
                QDomNode attack_delay=attack_delays.at(0);
                QDomElement attack_delay_element=attack_delay.toElement();
                players[i]->information.base_attack_delay=attack_delay_element.text().toInt();

            }


            //---------------------------------------------------defence Building
            if(build_element.attribute("type")=="defence"){

                //----------------------------------------------defence name
                QDomNodeList defence_names=build_element.elementsByTagName("name");
                QDomNode defence_name=defence_names.at(0);
                QDomElement defence_name_element=defence_name.toElement();
                players[i]->information.defence_name=defence_name_element.text();

                //----------------------------------------------defence cost
                QDomNodeList defence_costs=build_element.elementsByTagName("cost");
                QDomNode defence_cost=defence_costs.at(0);
                QDomElement defence_cost_element=defence_cost.toElement();
                players[i]->information.defence_cost=defence_cost_element.text().toInt();

                //----------------------------------------------defence upgrade_cost
                QDomNodeList defence_upgrade_costs=build_element.elementsByTagName("upgrade_cost");
                QDomNode defence_upgrade_cost=defence_upgrade_costs.at(0);
                QDomElement defence_upgrade_cost_element=defence_upgrade_cost.toElement();
                players[i]->information.defence_upgrade_cost=defence_upgrade_cost_element.text().toInt();

                //----------------------------------------------construction time
                QDomNodeList construction_times=build_element.elementsByTagName("construction_time");
                QDomNode construction_time=construction_times.at(0);
                QDomElement construction_time_element=construction_time.toElement();
                players[i]->information.defence_time_constructoin=construction_time_element.text().toInt();

                //----------------------------------------------max health
                QDomNodeList max_healths=build_element.elementsByTagName("max_health");
                QDomNode max_health=max_healths.at(0);
                QDomElement max_health_element=max_health.toElement();
                players[i]->information.defence_max_health=max_health_element.text().toInt();

                //----------------------------------------------attack_damage
                QDomNodeList attack_damages=build_element.elementsByTagName("attack_damage");
                QDomNode attack_damage=attack_damages.at(0);
                QDomElement attack_damage_element=attack_damage.toElement();
                players[i]->information.defence_attack_damage=attack_damage_element.text().toInt();

                //----------------------------------------------attack_range
                QDomNodeList attack_ranges=build_element.elementsByTagName("attack_range");
                QDomNode attack_range=attack_ranges.at(0);
                QDomElement attack_range_element=attack_range.toElement();
                players[i]->information.defence_attack_range=attack_range_element.text().toInt();

                //----------------------------------------------attack_delay
                QDomNodeList attack_delays=build_element.elementsByTagName("attack_delay");
                QDomNode attack_delay=attack_delays.at(0);
                QDomElement attack_delay_element=attack_delay.toElement();
                players[i]->information.defence_attack_delay=attack_delay_element.text().toInt();

            }


            //---------------------------------------------------money_maker Building
            if(build_element.attribute("type")=="money-maker"){

                //----------------------------------------------money_maker name
                QDomNodeList money_maker_names=build_element.elementsByTagName("name");
                QDomNode money_maker_name=money_maker_names.at(0);
                QDomElement money_maker_name_element=money_maker_name.toElement();
                players[i]->information.moneyMaker_name=money_maker_name_element.text();

                //----------------------------------------------money_maker cost
                QDomNodeList money_maker_costs=build_element.elementsByTagName("cost");
                QDomNode money_maker_cost=money_maker_costs.at(0);
                QDomElement money_maker_cost_element=money_maker_cost.toElement();
                players[i]->information.moneyMaker_cost=money_maker_cost_element.text().toInt();

                //----------------------------------------------money_maker upgrade_cost
                QDomNodeList money_maker_upgrade_costs=build_element.elementsByTagName("upgrade_cost");
                QDomNode money_maker_upgrade_cost=money_maker_upgrade_costs.at(0);
                QDomElement money_maker_upgrade_cost_element=money_maker_upgrade_cost.toElement();
                players[i]->information.moneyMaker_upgrade_cost=money_maker_upgrade_cost_element.text().toInt();

                //----------------------------------------------construction time
                QDomNodeList construction_times=build_element.elementsByTagName("construction_time");
                QDomNode construction_time=construction_times.at(0);
                QDomElement construction_time_element=construction_time.toElement();
                players[i]->information.moneyMaker_time_constructoin=construction_time_element.text().toInt();

                //----------------------------------------------max health
                QDomNodeList max_healths=build_element.elementsByTagName("max_health");
                QDomNode max_health=max_healths.at(0);
                QDomElement max_health_element=max_health.toElement();
                players[i]->information.moneyMaker_max_health=max_health_element.text().toInt();

                //----------------------------------------------attack_damage
                QDomNodeList attack_damages=build_element.elementsByTagName("attack_damage");
                QDomNode attack_damage=attack_damages.at(0);
                QDomElement attack_damage_element=attack_damage.toElement();
                players[i]->information.moneyMaker_attack_damage=attack_damage_element.text().toInt();

                //----------------------------------------------attack_range
                QDomNodeList attack_ranges=build_element.elementsByTagName("attack_range");
                QDomNode attack_range=attack_ranges.at(0);
                QDomElement attack_range_element=attack_range.toElement();
                players[i]->information.moneyMaker_attack_range=attack_range_element.text().toInt();

                //----------------------------------------------attack_delay
                QDomNodeList attack_delays=build_element.elementsByTagName("attack_delay");
                QDomNode attack_delay=attack_delays.at(0);
                QDomElement attack_delay_element=attack_delay.toElement();
                players[i]->information.moneyMaker_attack_delay=attack_delay_element.text().toInt();

                //-----------------------------------------------income
                QDomNodeList incomes=build_element.elementsByTagName("income");
                QDomNode income=incomes.at(0);
                QDomElement income_element=income.toElement();
                players[i]->information.moneyMaker_income=income_element.text().toInt();
            }

            //---------------------------------------------------unit maker Building
            if(build_element.attribute("type")=="unit-maker"){

                //----------------------------------------------money_maker name
                QDomNodeList money_maker_names=build_element.elementsByTagName("name");
                QDomNode money_maker_name=money_maker_names.at(0);
                QDomElement money_maker_name_element=money_maker_name.toElement();
                if(build_element.attribute("id")=="3")
                    players[i]->information.unitMaker_name=money_maker_name_element.text();
                if(build_element.attribute("id")=="4")
                    players[i]->information.super_unitMaker_name=money_maker_name_element.text();
                if(build_element.attribute("id")=="5")
                    players[i]->information.vehicle_unitMaker_name=money_maker_name_element.text();

                //----------------------------------------------money_maker cost
                QDomNodeList money_maker_costs=build_element.elementsByTagName("cost");
                QDomNode money_maker_cost=money_maker_costs.at(0);
                QDomElement money_maker_cost_element=money_maker_cost.toElement();
                if(build_element.attribute("id")=="3")
                    players[i]->information.unitMaker_cost=money_maker_cost_element.text().toInt();
                if(build_element.attribute("id")=="4")
                    players[i]->information.super_unitMaker_cost=money_maker_cost_element.text().toInt();
                if(build_element.attribute("id")=="5")
                    players[i]->information.vehicle_unitMaker_cost=money_maker_cost_element.text().toInt();

                //----------------------------------------------money_maker upgrade_cost
                QDomNodeList money_maker_upgrade_costs=build_element.elementsByTagName("upgrade_cost");
                QDomNode money_maker_upgrade_cost=money_maker_upgrade_costs.at(0);
                QDomElement money_maker_upgrade_cost_element=money_maker_upgrade_cost.toElement();
                if(build_element.attribute("id")=="3")
                    players[i]->information.unitMaker_upgrade_cost=money_maker_upgrade_cost_element.text().toInt();
                if(build_element.attribute("id")=="4")
                    players[i]->information.super_unitMaker_upgrade_cost=money_maker_upgrade_cost_element.text().toInt();
                if(build_element.attribute("id")=="5")
                    players[i]->information.vehicle_unitMaker_upgrade_cost=money_maker_upgrade_cost_element.text().toInt();

                //----------------------------------------------construction time
                QDomNodeList construction_times=build_element.elementsByTagName("construction_time");
                QDomNode construction_time=construction_times.at(0);
                QDomElement construction_time_element=construction_time.toElement();
                if(build_element.attribute("id")=="3")
                    players[i]->information.unitMaker_time_constructoin=construction_time_element.text().toInt();
                if(build_element.attribute("id")=="4")
                    players[i]->information.super_unitMaker_time_constructoin=construction_time_element.text().toInt();
                if(build_element.attribute("id")=="5")
                    players[i]->information.vehicle_unitMaker_time_constructoin=construction_time_element.text().toInt();

                //----------------------------------------------max health
                QDomNodeList max_healths=build_element.elementsByTagName("max_health");
                QDomNode max_health=max_healths.at(0);
                QDomElement max_health_element=max_health.toElement();
                if(build_element.attribute("id")=="3")
                    players[i]->information.unitMaker_max_health=max_health_element.text().toInt();
                if(build_element.attribute("id")=="4")
                    players[i]->information.super_unitMaker_max_health=max_health_element.text().toInt();
                if(build_element.attribute("id")=="5")
                    players[i]->information.vehicle_unitMaker_max_health=max_health_element.text().toInt();

                //----------------------------------------------attack_damage
                QDomNodeList attack_damages=build_element.elementsByTagName("attack_damage");
                QDomNode attack_damage=attack_damages.at(0);
                QDomElement attack_damage_element=attack_damage.toElement();
                if(build_element.attribute("id")=="3")
                    players[i]->information.unitMaker_attack_damage=attack_damage_element.text().toInt();
                if(build_element.attribute("id")=="4")
                    players[i]->information.super_unitMaker_attack_damage=attack_damage_element.text().toInt();
                if(build_element.attribute("id")=="5")
                    players[i]->information.vehicle_unitMaker_attack_damage=attack_damage_element.text().toInt();

                //----------------------------------------------attack_range
                QDomNodeList attack_ranges=build_element.elementsByTagName("attack_range");
                QDomNode attack_range=attack_ranges.at(0);
                QDomElement attack_range_element=attack_range.toElement();
                if(build_element.attribute("id")=="3")
                    players[i]->information.unitMaker_attack_range=attack_range_element.text().toInt();
                if(build_element.attribute("id")=="4")
                    players[i]->information.super_unitMaker_attack_range=attack_range_element.text().toInt();
                if(build_element.attribute("id")=="5")
                    players[i]->information.vehicle_unitMaker_attack_range=attack_range_element.text().toInt();

                //----------------------------------------------attack_delay
                QDomNodeList attack_delays=build_element.elementsByTagName("attack_delay");
                QDomNode attack_delay=attack_delays.at(0);
                QDomElement attack_delay_element=attack_delay.toElement();
                if(build_element.attribute("id")=="3")
                    players[i]->information.unitMaker_attack_delay=attack_delay_element.text().toInt();
                if(build_element.attribute("id")=="4")
                    players[i]->information.super_unitMaker_attack_delay=attack_delay_element.text().toInt();
                if(build_element.attribute("id")=="5")
                    players[i]->information.vehicle_unitMaker_attack_delay=attack_delay_element.text().toInt();

            }

        }

        //-------------------------------------------------------unit
        QDomNodeList units=team.elementsByTagName("unit");
        for(int j=0; j<units.count(); j++){
            QDomNode unit=units.at(j);
            QDomElement unit_element=unit.toElement();

            //---------------------------------------------------common unit
            if(unit_element.attribute("id","noUnit")=="noUnit")
                continue;

            //----------------------------------------------name
            QDomNodeList base_names=unit_element.elementsByTagName("name");
            QDomNode base_name=base_names.at(0);
            QDomElement base_name_element=base_name.toElement();
            if(unit_element.attribute("id")=="6")
                players[i]->information.normal_name=base_name_element.text();
            if(unit_element.attribute("id")=="7")
                players[i]->information.super_name=base_name_element.text();
            if(unit_element.attribute("id")=="8")
                players[i]->information.vehicle_name=base_name_element.text();

            //----------------------------------------------cost
            QDomNodeList base_costs=unit_element.elementsByTagName("cost");
            QDomNode base_cost=base_costs.at(0);
            QDomElement base_cost_element=base_cost.toElement();
            if(unit_element.attribute("id")=="6")
                players[i]->information.normal_cost=base_cost_element.text().toInt();
            if(unit_element.attribute("id")=="7")
                players[i]->information.super_cost=base_cost_element.text().toInt();
            if(unit_element.attribute("id")=="8")
                players[i]->information.vehicle_cost=base_cost_element.text().toInt();

            //----------------------------------------------train time
            QDomNodeList construction_times=unit_element.elementsByTagName("train_time");
            QDomNode construction_time=construction_times.at(0);
            QDomElement construction_time_element=construction_time.toElement();
            if(unit_element.attribute("id")=="6")
                players[i]->information.normal_time_constructoin=construction_time_element.text().toInt();
            if(unit_element.attribute("id")=="7")
                players[i]->information.super_time_constructoin=construction_time_element.text().toInt();
            if(unit_element.attribute("id")=="8")
                players[i]->information.vehicle_time_constructoin=construction_time_element.text().toInt();

            //----------------------------------------------max health
            QDomNodeList max_healths=unit_element.elementsByTagName("max_health");
            QDomNode max_health=max_healths.at(0);
            QDomElement max_health_element=max_health.toElement();
            if(unit_element.attribute("id")=="6")
                players[i]->information.normal_max_health=max_health_element.text().toInt();
            if(unit_element.attribute("id")=="7")
                players[i]->information.super_max_health=max_health_element.text().toInt();
            if(unit_element.attribute("id")=="8")
                players[i]->information.vehicle_max_health=max_health_element.text().toInt();

            //----------------------------------------------attack_damage
            QDomNodeList attack_damages=unit_element.elementsByTagName("attack_damage");
            QDomNode attack_damage=attack_damages.at(0);
            QDomElement attack_damage_element=attack_damage.toElement();
            if(unit_element.attribute("id")=="6")
                players[i]->information.normal_attack_damage=attack_damage_element.text().toInt();
            if(unit_element.attribute("id")=="7")
                players[i]->information.super_attack_damage=attack_damage_element.text().toInt();
            if(unit_element.attribute("id")=="8")
                players[i]->information.vehicle_attack_damage=attack_damage_element.text().toInt();

            //----------------------------------------------attack_range
            QDomNodeList attack_ranges=unit_element.elementsByTagName("attack_range");
            QDomNode attack_range=attack_ranges.at(0);
            QDomElement attack_range_element=attack_range.toElement();
            if(unit_element.attribute("id")=="6")
                players[i]->information.normal_attack_range=attack_range_element.text().toInt();
            if(unit_element.attribute("id")=="7")
                players[i]->information.super_attack_range=attack_range_element.text().toInt();
            if(unit_element.attribute("id")=="8")
                players[i]->information.vehicle_attack_range=attack_range_element.text().toInt();

            //----------------------------------------------attack_delay
            QDomNodeList attack_delays=unit_element.elementsByTagName("attack_delay");
            QDomNode attack_delay=attack_delays.at(0);
            QDomElement attack_delay_element=attack_delay.toElement();
            if(unit_element.attribute("id")=="6")
                players[i]->information.normal_attack_delay=attack_delay_element.text().toInt();
            if(unit_element.attribute("id")=="7")
                players[i]->information.super_attack_delay=attack_delay_element.text().toInt();
            if(unit_element.attribute("id")=="8")
                players[i]->information.vehicle_attack_delay=attack_delay_element.text().toInt();

            //----------------------------------------------speed
            QDomNodeList speeds=unit_element.elementsByTagName("speed");
            QDomNode speed=speeds.at(0);
            QDomElement speed_element=speed.toElement();
            if(unit_element.attribute("id")=="6")
                players[i]->information.normal_speed=speed_element.text().toInt();
            if(unit_element.attribute("id")=="7")
                players[i]->information.super_speed=speed_element.text().toInt();
            if(unit_element.attribute("id")=="8")
                players[i]->information.vehicle_speed=speed_element.text().toInt();

            //----------------------------------------------max_mana   spcial_damage  mana_regen
            if(unit_element.attribute("id")=="7"){

                QDomNodeList special_attack_damages=unit_element.elementsByTagName("special_attack_damage");
                QDomNode special_attack_damage=special_attack_damages.at(0);
                QDomElement special_attack_damage_element=special_attack_damage.toElement();
                players[i]->information.super_attack_special_damage=special_attack_damage_element.text().toInt();


                QDomNodeList max_manas=unit_element.elementsByTagName("max_mana");
                QDomNode max_mana=max_manas.at(0);
                QDomElement max_mana_element=max_mana.toElement();
                players[i]->information.super_max_mana=max_mana_element.text().toInt();


                QDomNodeList regen_manas=unit_element.elementsByTagName("mana_regen");
                QDomNode regen_mana=regen_manas.at(0);
                QDomElement regen_mana_element=regen_mana.toElement();
                players[i]->information.super_regenition=regen_mana_element.text().toInt();

            }

            //---------------------------------------------capacity
            if(unit_element.attribute("id")=="8"){

                QDomNodeList capacitys=unit_element.elementsByTagName("capacity");
                QDomNode capacity=capacitys.at(0);
                QDomElement capacity_element=capacity.toElement();
                players[i]->information.vehicle_capacity=capacity_element.text().toInt();
            }
  /**/
      }

    }//end for each team

    //----------------------------------------------------read Zombie information

    QDomNodeList zombies=root.elementsByTagName("zombie");

    QDomNode zombie = zombies.at(0);
    QDomElement zombie_el = zombie.toElement();

    //------------------------------------------------------max_health
    QDomNodeList zombie_max_healths = zombie_el.elementsByTagName("max_health");
    QDomNode zzombie_max_health = zombie_max_healths.at(0);
    QDomElement zombie_max_health_el = zzombie_max_health.toElement();
    Zombie::zombie_max_health=zombie_max_health_el.text().toInt();

    //------------------------------------------------------attack_damage
    QDomNodeList zombie_attack_damages = zombie_el.elementsByTagName("attack_damage");
    QDomNode zzombie_attack_damage = zombie_attack_damages.at(0);
    QDomElement zombie_attack_damage_el = zzombie_attack_damage.toElement();
    Zombie::zombie_attack_damage=zombie_attack_damage_el.text().toInt();

    //------------------------------------------------------attack_range
    QDomNodeList zombie_attack_ranges = zombie_el.elementsByTagName("attack_range");
    QDomNode zzombie_attack_range = zombie_attack_ranges.at(0);
    QDomElement zombie_attack_range_el = zzombie_attack_range.toElement();
    Zombie::zombie_attack_range=zombie_attack_range_el.text().toInt();

    //------------------------------------------------------attack_delay
    QDomNodeList zombie_attack_delays = zombie_el.elementsByTagName("attack_delay");
    QDomNode zzombie_attack_delay = zombie_attack_delays.at(0);
    QDomElement zombie_attack_delay_el = zzombie_attack_delay.toElement();
    Zombie::zombie_attack_delay=zombie_attack_delay_el.text().toInt();

    //------------------------------------------------------speed
    QDomNodeList zombie_speeds = zombie_el.elementsByTagName("speed");
    QDomNode zzombie_speed = zombie_speeds.at(0);
    QDomElement zombie_speed_el = zzombie_speed.toElement();
    Zombie::zombie_speed=zombie_speed_el.text().toInt();

    //------------------------------------------------------spawn_period
    QDomNodeList zombie_spawn_periods = zombie_el.elementsByTagName("spawn_period");
    QDomNode zzombie_spawn_period = zombie_spawn_periods.at(0);
    QDomElement zombie_spawn_period_el = zzombie_spawn_period.toElement();
    Zombie::zombie_spawn_period=zombie_spawn_period_el.text().toInt();

    //------------------------------------------------------spawn_count
    QDomNodeList zombie_spawn_counts = zombie_el.elementsByTagName("spawn_count");
    QDomNode zzombie_spawn_count = zombie_spawn_counts.at(0);
    QDomElement zombie_spawn_count_el = zzombie_spawn_count.toElement();
    Zombie::zombie_spawn_count=zombie_spawn_count_el.text().toInt();
}
