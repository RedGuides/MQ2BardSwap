---
tags:
  - plugin
resource_link: "https://www.redguides.com/community/resources/mq2bardswap.102/"
support_link: "https://www.redguides.com/community/threads/mq2bardswap.66807/"
repository: "https://github.com/RedGuides/MQ2BardSwap"
config: "MQ2BardSwap_character_server.ini"
authors: "Cr4zyb4rd, eqmule, Knightly, brainiac"
tagline: "Swap the appropriate instrument into your primary or second slot"
---

# MQ2BardSwap
<!--desc-start-->
This plugin attempts to retrieve the current song from MQ2Twist and if that TLO exists, it will swap the appropriate instrument into your primary or second slot.
<!--desc-end-->

## Commands

<a href="cmd-bardswap/">
{% 
  include-markdown "projects/mq2bardswap/cmd-bardswap.md" 
  start="<!--cmd-syntax-start-->" 
  end="<!--cmd-syntax-end-->" 
%}
</a>
:    {% include-markdown "projects/mq2bardswap/cmd-bardswap.md" 
        start="<!--cmd-desc-start-->" 
        end="<!--cmd-desc-end-->" 
        trailing-newlines=false 
     %} {{ readMore('projects/mq2bardswap/cmd-bardswap.md') }}

## Settings

Here's a sample `MQ2BardSwap_character_server.ini`

```ini
[Settings]
; instrument swapping using ITEMID and SLOTID
Horn=/exchange 68773 13                                     
Drum=/exchange "Illdaera's Steel Drum" mainhand   
; Can use mainhand or offhand for each instrument                 
Lute=/exchange "Bassy Mandola of Tsepir" mainhand
Wind=DISABLED
Singing=DISABLED
Weapons=/exchange "Worn Iksar Cleaver" mainhand
Delay=21
[Exclude]
;instruments don't have an effect on these
exclude1=Requiem of Time
exclude2=Selo's Rhythm of Speed
exclude3=Selo`s Assonant Strane
exclude4=Song of Sustenance
exclude5=Alenia`s Disenchanting Melody
;no swap for my Composers Greaves click please
exclude6=Selo`s Accelerating Chorus
;or lute of the flowing waters click
exclude7=Wind of Marr
```

For reference, here's a list of [Slot names](../macroquest/reference/general/slot-names.md) and numbers.

## Top-Level Objects

## [BardSwap](tlo-bardswap.md)
{% include-markdown "projects/mq2bardswap/tlo-bardswap.md" start="<!--tlo-desc-start-->" end="<!--tlo-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2bardswap/tlo-bardswap.md') }}

## DataTypes

## [swap](datatype-swap.md)
{% include-markdown "projects/mq2bardswap/datatype-swap.md" start="<!--dt-desc-start-->" end="<!--dt-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2bardswap/datatype-swap.md') }}

<h2>Members</h2>
{% include-markdown "projects/mq2bardswap/datatype-swap.md" start="<!--dt-members-start-->" end="<!--dt-members-end-->" %}
{% include-markdown "projects/mq2bardswap/datatype-swap.md" start="<!--dt-linkrefs-start-->" end="<!--dt-linkrefs-end-->" %}
