@tool
extends Component
class_name DamageComponent

@export var Damage:int = 10
@export var DamType:int = 1

func get_component() -> Dictionary[String, Variant]:
	return {
		"Damage" : FormatWriter.format(Damage, "Damage"),
		"DamType" : FormatWriter.format(DamType, "DamType"),
	}
