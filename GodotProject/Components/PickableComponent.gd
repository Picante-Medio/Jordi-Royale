@tool
extends Component
class_name PickableComponent

@export var pickupRadius:float = 0.5

func get_component() -> Dictionary[String, Variant]:
	return {
		"pickupRadius" : FormatWriter.format(pickupRadius, "pickupRadius"),
	}
