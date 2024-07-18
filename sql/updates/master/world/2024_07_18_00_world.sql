-- QUEST_SPECIAL_FLAGS_project_DAILY_QUEST = 0x01000000

delete
    quest_template_addon,
    quest_template
from quest_template_addon
         inner join quest_template on quest_template.ID = quest_template_addon.ID
where quest_template_addon.SpecialFlags & 0x01000000 > 0;


-- delete orphan quest objectives
delete quest_objective
from quest_objective
where not exists (select 1 from quest_template where ID = quest_objective.questId);

-- delete orphan quest objectives locale
delete quest_objectives_locale
from quest_objectives_locale
where not exists (select 1 from quest_template where ID = quest_objectives_locale.QuestId);

-- delete orphan quest offer reward
delete quest_offer_reward
from quest_offer_reward
where not exists (select 1 from quest_template where ID = quest_offer_reward.ID);

-- delete orphan quest offer reward locale
delete quest_offer_reward_locale
from quest_offer_reward_locale
where not exists (select 1 from quest_template where ID = quest_offer_reward_locale.ID);

-- delete orphan quest poi
delete quest_poi
from quest_poi
where not exists (select 1 from quest_template where ID = quest_poi.QuestID);

-- delete orphan quest poi points
delete quest_poi_points
from quest_poi_points
where not exists (select 1 from quest_template where ID = quest_poi_points.QuestID);

-- delete orphan quest request items
delete quest_request_items
from quest_request_items
where not exists (select 1 from quest_template where ID = quest_request_items.ID);

-- delete orphan quest request items locale
delete quest_request_items_locale
from quest_request_items_locale
where not exists (select 1 from quest_template where ID = quest_request_items_locale.ID);

-- delete orphan quest template locale
delete quest_template_locale
from quest_template_locale
where not exists (select 1 from quest_template where ID = quest_template_locale.ID);

-- delete orphan creature questender
delete creature_questender
from creature_questender
where not exists (select 1 from quest_template where ID = creature_questender.quest);

-- delete orphan creature queststarter
delete creature_queststarter
from creature_queststarter
where not exists (select 1 from quest_template where ID = creature_queststarter.quest);
