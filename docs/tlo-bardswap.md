---
tags:
  - tlo
---
# `BardSwap`

<!--tlo-desc-start-->
Grants access to the "swap" datatype
<!--tlo-desc-end-->

## Forms
<!--tlo-forms-start-->
### {{ renderMember(type='bool', name='BardSwap') }}

:   indicates whether mq2bardswap is enabled

<!--tlo-forms-end-->

## Associated DataTypes
<!--tlo-datatypes-start-->
## [`swap`](datatype-swap.md)
{% include-markdown "projects/mq2bardswap/datatype-swap.md" start="<!--dt-desc-start-->" end="<!--dt-desc-end-->" trailing-newlines=false %} {{ readMore('projects/mq2bardswap/datatype-swap.md') }}
:    <h3>Members</h3>
    {% include-markdown "projects/mq2bardswap/datatype-swap.md" start="<!--dt-members-start-->" end="<!--dt-members-end-->" %}
    {% include-markdown "projects/mq2bardswap/datatype-swap.md" start="<!--dt-linkrefs-start-->" end="<!--dt-linkrefs-end-->" %}
    <!--tlo-datatypes-end-->

## Examples
<!--tlo-examples-start-->
- To see if BardSwap is enabled,
`/echo ${BardSwap}`
<!--tlo-examples-end-->

<!--tlo-linkrefs-start-->
[bool]: ../macroquest/reference/data-types/datatype-bool.md
<!--tlo-linkrefs-end-->