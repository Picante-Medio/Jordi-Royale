@tool
extends Component
class_name JumpPowerComponent

<<<<<<< HEAD

func get_component() -> Dictionary[String, Variant]:
	return {
=======
@export var power:float

func get_component() -> Dictionary[String, Variant]:
	return {
		"power" : FormatWriter.format(power, "power"),
>>>>>>> f2e822d (proyecto de godot en proceso)
	}
