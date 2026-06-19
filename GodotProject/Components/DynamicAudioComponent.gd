@tool
extends Component
class_name DynamicAudioComponent

@export var maxVolume:float = 1.0
@export var minVolume:float = .0
@export var audioName:String = ""
@export var interpolationMiliseconds:float = 1500.0

func get_component() -> Dictionary[String, Variant]:
	return {
		"maxVolume" : FormatWriter.format(maxVolume, "maxVolume"),
		"minVolume" : FormatWriter.format(minVolume, "minVolume"),
		"audioName" : FormatWriter.format(audioName, "audioName"),
		"interpolationMiliseconds" : FormatWriter.format(interpolationMiliseconds, "interpolationMiliseconds"),
	}
