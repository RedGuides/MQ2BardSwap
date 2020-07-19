# MQ2BardSwap

This plugin attempts to retrieve the current song from MQ2Twist and if that TLO exists, it will swap the appropriate instrument into your primary or second slot.

## Usage

```txt
/bardswap - Toggle swapping on and off.
/bardswap melee - Toggle using "Melee swap" delay.
```

## Slot IDs

```txt
13= Mainhand
14= Offhand
```

## Example ini

MQ2BardSwap_Someplayer_Someserver.ini

```ini
[Settings]
;instrument swapping using ITEMID and SLOTID
Horn=/exchange 68773 13
;Can use mainhand or offhand for each instrument
Drum=/exchange "Illdaera's Steel Drum" mainhand
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
