@tool
extends Component
class_name JumpPowerComponent

@export var power:float = 10.

func get_component() -> Dictionary[String, Variant]:
	return {
		"power" : FormatWriter.format(power, "power"),
	}
