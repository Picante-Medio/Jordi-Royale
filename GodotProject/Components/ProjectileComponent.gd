@tool
extends Component
class_name ProjectileComponent

@export var lifetime:int
@export var pathTypeX:int = 0
@export var pathInfoX:Vector4 = Vector4(0., 0., 0., 0.)
@export var pathTypeY:int = 0
@export var pathInfoY:Vector4 = Vector4(0., 0., 0., 0.)
@export var pathTypeZ:int = 0
@export var pathInfoZ:Vector4 = Vector4(0., 0., 0., 0.)

func get_component() -> Dictionary[String, Variant]:
	return {
		"lifetime" : FormatWriter.format(lifetime, "lifetime"),
		"pathTypeX" : FormatWriter.format(pathTypeX, "pathTypeX"),
		"pathInfoX" : FormatWriter.format(pathInfoX, "pathInfoX"),
		"pathTypeY" : FormatWriter.format(pathTypeY, "pathTypeY"),
		"pathInfoY" : FormatWriter.format(pathInfoY, "pathInfoY"),
		"pathTypeZ" : FormatWriter.format(pathTypeZ, "pathTypeZ"),
		"pathInfoZ" : FormatWriter.format(pathInfoZ, "pathInfoZ"),
	}
