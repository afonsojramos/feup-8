@extends('layouts.app')

@section('content')
<div class="list-group container">
    @foreach ($exercises as $exercise)
    <div >{{ $exercise->title}} </div>
    @endforeach

    <div style="margin-left: -2.5%;" class="rounded">
        {{ $exercises->links() }}
    </div>
</div>
@endsection
