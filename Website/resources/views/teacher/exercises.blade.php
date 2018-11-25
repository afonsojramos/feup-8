@extends('layouts.app')

@section('content')
<div class="container">
    @foreach ($exercises as $exercise)
    <div >{{ $exercise->title}} </div>
    @endforeach
</div>
@endsection
