(function(window){
function DayHandle(timeObj){
var selectedYear = $(".year", timeObj).val();
var selectedMonth = $(".month option:selected", timeObj).prop("value");
$(".day  option[value=29]", timeObj).remove();
$(".day  option[value=30]", timeObj).remove();
$(".day  option[value=31]", timeObj).remove();
if(selectedMonth == 2){
if((selectedYear % 4 == 0 && selectedYear %100 != 0) || (selectedYear % 400 == 0)){
$(".day", timeObj).append("<option value='29'>29</option>");
}else{
}
} else if(((selectedMonth <= 7) && (selectedMonth % 2 == 0)) || ((selectedMonth >= 8) && (selectedMonth % 2 == 1))){
$(".day", timeObj).append("<option value='29'>29</option>");
$(".day", timeObj).append("<option value='30'>30</option>");
} else {
$(".day", timeObj).append("<option value='29'>29</option>");
$(".day", timeObj).append("<option value='30'>30</option>");
$(".day", timeObj).append("<option value='31'>31</option>");
}
}
function InitDateTimeEvent(timeObj)
{
timeObj.on("change", ".month,.year", function(event){
DayHandle(timeObj);
event.stopPropagation();
});
}
function InitDateTimeTemplate(template, controlID)
{
var timeSelector = "[id='"+controlID+"']";
var timeObj = $(timeSelector, template);
DayHandle(timeObj);
InitDateTimeEvent(timeObj)
}
window.InitDateTimeTemplate = InitDateTimeTemplate;
})(window);
