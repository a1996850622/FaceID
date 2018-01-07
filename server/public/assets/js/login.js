var socketio = io.connect(location.host);

window.onload = function(){
	$('.face_recognition').on("click", function(){
		//var recognition_value = document.getElementById("face_recognition");
		$(".face_recognition").prop("disabled", true);
		//recognition_value.value = "辨識中...";

		socketio.emit("recognition_on");
	});
}

socketio.on("verification_successful", function(data) {
    $(".face_recognition").prop("disabled", false);

    window.location.href = "/apis/FaceLogin";

});