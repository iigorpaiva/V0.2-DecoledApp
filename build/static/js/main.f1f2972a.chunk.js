(this.webpackJsonpdecoled=this.webpackJsonpdecoled||[]).push([[0],{1:function(e,a,t){e.exports=t.p+"static/media/logo.c67d3419.svg"},12:function(e,a,t){e.exports=t(19)},17:function(e,a,t){},18:function(e,a,t){},19:function(e,a,t){"use strict";t.r(a);var n=t(0),l=t.n(n),o=t(5),r=t.n(o),c=(t(17),t(6)),s=t(7),i=t(9),h=t(8),m=t(10),d=t(1),p=t.n(d),u=(t(18),t(2)),g=t(22),v=t(3),b=t.n(v),f=function(e){function a(e){var t;return Object(c.a)(this,a),(t=Object(i.a)(this,Object(h.a)(a).call(this,e))).handleChange1=function(e){fetch("/led1",{method:"PUT",body:e}).then((function(e){return e.text()})).then(t.setState({value1:e}))},t.handleChange2=function(e){fetch("/led2",{method:"PUT",body:e}).then((function(e){return e.text()})).then(t.setState({value2:e}))},t.handleChangeTime1=function(e){fetch("/time1",{method:"PUT",body:e}).then((function(e){return e.text()})).then(t.setState({time1:e})).then(console.log(e))},t.handleChangeTime2=function(e){fetch("/time2",{method:"PUT",body:e}).then((function(e){return e.text()})).then(t.setState({time2:e})).then(console.log(e))},t.state={value1:0,value2:0,time1:"00:00",time2:"00:00"},t}return Object(m.a)(a,e),Object(s.a)(a,[{key:"render",value:function(){return l.a.createElement("div",{className:"App"},l.a.createElement("header",{className:"App-header"},l.a.createElement("body",{"data-spy":"scroll","data-target":"#lambda-navbar","data-offset":"0"},l.a.createElement("nav",{class:"navbar navbar-expand-md navbar-dark navbar-transparent fixed-top sticky-navigation",id:"lambda-navbar"},l.a.createElement("a",{class:"navbar-brand",href:""},"Decoled App"),l.a.createElement("button",{class:"navbar-toggler navbar-toggler-right border-0",type:"button","data-toggle":"collapse","data-target":"#navbarCollapse","aria-controls":"navbarCollapse","aria-expanded":"false","aria-label":"Toggle navigation"},l.a.createElement("span",{"data-feather":"menu"})),l.a.createElement("div",{class:"collapse navbar-collapse",id:"navbarCollapse"},l.a.createElement("ul",{class:"navbar-nav ml-auto"},l.a.createElement("li",{class:"nav-item"},l.a.createElement("a",{class:"nav-link page-scroll",href:"#principal"},"Sala")),l.a.createElement("li",{class:"nav-item"},l.a.createElement("a",{class:"nav-link page-scroll",href:"#hall"},"Hall")),l.a.createElement("li",{class:"nav-item"},l.a.createElement("a",{class:"nav-link page-scroll",href:"#controle"},"Controle")))))),l.a.createElement("section",{class:"App-trans",id:"principal"},l.a.createElement("img",{src:p.a,className:"App-logo",alt:"logo"}),l.a.createElement("h1",{className:"App-title"},"Sala"),l.a.createElement(g.a,null,l.a.createElement(u.CircleSlider,{onChange:this.handleChange1,value:this.state.value1,size:150,showTooltip:!0,gradientColorFrom:"#009f5c",gradientColorTo:"#006b5c",showPercentage:!0,tooltipColor:"#6ab6e1",stepSize:20}))),l.a.createElement("section",{class:"App-trans",id:"hall"},l.a.createElement("img",{src:p.a,className:"App-logo",alt:"logo"}),l.a.createElement("h1",{className:"App-title"},"Hall"),l.a.createElement(g.a,null,l.a.createElement(u.CircleSlider,{onChange:this.handleChange2,value:this.state.value4,size:140,showTooltip:!0,gradientColorFrom:"#009f5c",gradientColorTo:"#006b5c",showPercentage:!0,tooltipColor:"#6ab6e1",stepSize:20}))),l.a.createElement("section",{class:"App-trans",id:"controle"},l.a.createElement(g.a,null,l.a.createElement("h1",{className:"App-title"},"In\xedcio"),l.a.createElement(b.a,{onChange:this.handleChangeTime1,color:"#072c07",inputVisible:!0}),l.a.createElement("h1",{className:"App-title"},"Final"),l.a.createElement(b.a,{value:this.state.time,onChange:this.handleChangeTime2,color:"#072c07",inputVisible:!0,style:{size:50}})))))}}]),a}(n.Component);Boolean("localhost"===window.location.hostname||"[::1]"===window.location.hostname||window.location.hostname.match(/^127(?:\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)){3}$/));r.a.render(l.a.createElement(f,null),document.getElementById("root")),"serviceWorker"in navigator&&navigator.serviceWorker.ready.then((function(e){e.unregister()})).catch((function(e){console.error(e.message)}))}},[[12,1,2]]]);
//# sourceMappingURL=main.f1f2972a.chunk.js.map