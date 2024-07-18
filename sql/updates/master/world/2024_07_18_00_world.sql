-- QUEST_SPECIAL_FLAGS_project_DAILY_QUEST = 0x01000000

delete
    quest_template_addon,
    quest_template
from
    quest_template_addon inner join quest_template on quest_template.ID = quest_template_addon.ID
where
    quest_template_addon.SpecialFlags & 0x01000000 > 0;
